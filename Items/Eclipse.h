#ifndef PA_PROJ_ECLIPSE_H
#define PA_PROJ_ECLIPSE_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

template<ChampionConcept OffensiveChamp>
class EclipsePassive:public ItemSkill<OffensiveChamp>{
public:
    static int cooldownLeft;
    static int attacks;
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double PhysDamage(){return (attacks==1)*(OffensiveChamp::IsRanged?0.04:0.08)*(DefendingChamp::TotalHP());}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){
        cooldownLeft=((ChampionSkill::onAttack||ChampionSkill::ability)&&(attacks==1))?6*Skill::TicksPerSecond:cooldownLeft>0?cooldownLeft-1:0;
        attacks=(ChampionSkill::onAttack||ChampionSkill::ability)?(cooldownLeft>0?0:attacks==1?0:1):attacks;
    }

    class WaitTick:public ItemSkill<OffensiveChamp>{
    public:
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            cooldownLeft=cooldownLeft>0?cooldownLeft-1:0;
        }
    };
};
template<ChampionConcept OffensiveChamp> int EclipsePassive<OffensiveChamp>::cooldownLeft=0;
template<ChampionConcept OffensiveChamp> int EclipsePassive<OffensiveChamp>::attacks=0;

class Eclipse: public Item{
public:
    constexpr static double cost=2800;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=EclipsePassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChampion>
    using WaitTick=EclipsePassive<OffensiveChampion>::WaitTick;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double Eclipse::StatValue<AD>(){return 70;}

#endif //PA_PROJ_ECLIPSE_H
