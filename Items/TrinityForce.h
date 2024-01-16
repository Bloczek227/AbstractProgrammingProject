#ifndef PA_PROJ_TRINITYFORCE_H
#define PA_PROJ_TRINITYFORCE_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

template<ChampionConcept OffensiveChamp>
class TrinityForcePassive:public ItemSkill<OffensiveChamp>{
public:
    static int cooldownLeft;
    static int usageTimeLeft;
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double PhysDamage(){
        return (ChampionSkill::onHit&&(usageTimeLeft>0||(cooldownLeft==0&&ChampionSkill::ability)))*(2*OffensiveChamp::BaseAD());
    }
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){
        cooldownLeft=ChampionSkill::onHit&&(usageTimeLeft>0||(cooldownLeft==0&&ChampionSkill::ability))?15*Skill::TicksPerSecond/10:cooldownLeft;
        usageTimeLeft=ChampionSkill::onHit?0:(ChampionSkill::ability&&(usageTimeLeft>0||cooldownLeft==0))?10*Skill::TicksPerSecond:usageTimeLeft;
    }
    static void reset(){
        cooldownLeft=0;
        usageTimeLeft=0;
    }

    class WaitTick:public ItemSkill<OffensiveChamp>{
    public:
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            usageTimeLeft=usageTimeLeft>0?usageTimeLeft-1:0;
            cooldownLeft=cooldownLeft>0?cooldownLeft-1:0;
        }
    };
};
template<ChampionConcept OffensiveChamp> int TrinityForcePassive<OffensiveChamp>::cooldownLeft=0;
template<ChampionConcept OffensiveChamp> int TrinityForcePassive<OffensiveChamp>::usageTimeLeft=0;

class TrinityForce: public Item{
public:
    constexpr static double cost=3333;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=TrinityForcePassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChampion>
    using WaitTick = TrinityForcePassive<OffensiveChampion>::WaitTick;
    template<ChampionConcept OffensiveChamp> static void reset(){SkillType<OffensiveChamp>::reset();}
};
template<> double TrinityForce::StatValue<AD>(){return 45;}
template<> double TrinityForce::StatValue<AttackSpeed>(){return 33;}
template<> double TrinityForce::StatValue<HP>(){return 300;}

#endif //PA_PROJ_TRINITYFORCE_H
