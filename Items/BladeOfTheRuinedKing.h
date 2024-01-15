//
// Created by aaa22 on 24.12.2023.
//

#ifndef PA_PROJ_BLADEOFTHERUINEDKING_H
#define PA_PROJ_BLADEOFTHERUINEDKING_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"

template<ChampionConcept OffensiveChamp>
class BladeOfTheRuinedKingPassive:public ItemSkill<OffensiveChamp>{
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double PhysDamage(){return (ChampionSkill::onHit*(OffensiveChamp::IsRanged?0.09:0.12)*DefendingChamp::CurrentHP)>15?
                                      (ChampionSkill::onHit*(OffensiveChamp::IsRanged?0.09:0.12)*DefendingChamp::CurrentHP):15;}
};

class BladeOfTheRuinedKing: public Item{
public:
    constexpr static double cost=3200;
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=BladeOfTheRuinedKingPassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double BladeOfTheRuinedKing::StatValue<AD>(){return 40;}
template<> double BladeOfTheRuinedKing::StatValue<AttackSpeed>(){return 25;}

#endif //PA_PROJ_BLADEOFTHERUINEDKING_H
