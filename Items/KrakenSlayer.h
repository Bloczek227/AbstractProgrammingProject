//
// Created by aaa22 on 23.12.2023.
//

#ifndef PA_PROJ_KRAKENSLAYER_H
#define PA_PROJ_KRAKENSLAYER_H

#include "../stats.h"
#include "../skill.h"
#include "../item.h"
#include "../helpers.h"

template<ChampionConcept OffensiveChamp>
class KrakenSlayerPassive:public ItemSkill<OffensiveChamp>{
    static int counter;
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double TrueDamage(){return (counter==2&&(ChampionSkill::onHit||ChampionSkill::onAttack))*
                                      (calculateReluFunction(35,9,5,OffensiveChamp::lv)+0.65*OffensiveChamp::TotalAD()+0.6*OffensiveChamp::TotalAP())*
                                      (2-DefendingChamp::CurrentHP/DefendingChamp::TotalHP());}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){
        counter=(counter+(ChampionSkill::onHit||ChampionSkill::onAttack))%3;
    }
    static void reset(){
        counter=0;
    }
};

template<ChampionConcept OffensiveChamp> int KrakenSlayerPassive<OffensiveChamp>::counter=0;
class KrakenSlayer: public Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=KrakenSlayerPassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp>
    static void reset(){SkillType<OffensiveChamp>::reset();}
};
template<> double KrakenSlayer::StatValue<AD>(){return 40;}
template<> double KrakenSlayer::StatValue<AttackSpeed>(){return 35;}
template<> double KrakenSlayer::StatValue<CriticalChance>(){return 20;}

#endif //PA_PROJ_KRAKENSLAYER_H
