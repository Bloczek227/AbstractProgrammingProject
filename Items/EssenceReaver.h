#ifndef PA_PROJ_ESSENCEREAVER_H
#define PA_PROJ_ESSENCEREAVER_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

template<ChampionConcept OffensiveChamp>
class EssenceReaverPassive:public ItemSkill<OffensiveChamp>{
public:
    static int cooldownLeft;
    static int usageTimeLeft;
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double PhysDamage(){
        return (ChampionSkill::onHit&&(usageTimeLeft>0||(cooldownLeft==0&&ChampionSkill::ability)))*(1.4*OffensiveChamp::BaseAD()+0.2*OffensiveChamp::BonusAD());
    }
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){
        cooldownLeft=ChampionSkill::onHit&&(usageTimeLeft>0||(cooldownLeft==0&&ChampionSkill::ability))?15*Skill::TicksPerSecond/10:cooldownLeft;
        usageTimeLeft=ChampionSkill::onHit?0:(ChampionSkill::ability&&(usageTimeLeft>0||cooldownLeft==0))?10*Skill::TicksPerSecond:usageTimeLeft;
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
template<ChampionConcept OffensiveChamp> int EssenceReaverPassive<OffensiveChamp>::cooldownLeft=0;
template<ChampionConcept OffensiveChamp> int EssenceReaverPassive<OffensiveChamp>::usageTimeLeft=0;

class EssenceReaver: public Item{
public:
    constexpr static double cost=2900;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=EssenceReaverPassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChampion>
    using WaitTick=EssenceReaverPassive<OffensiveChampion>::WaitTick;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double EssenceReaver::StatValue<AD>(){return 55;}
template<> double EssenceReaver::StatValue<CriticalChance>(){return 20;}

#endif //PA_PROJ_ESSENCEREAVER_H
