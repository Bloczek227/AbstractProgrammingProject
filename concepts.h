#ifndef PA_PROJ_CONCEPTS_H
#define PA_PROJ_CONCEPTS_H

#include <concepts>
#include "stats.h"

template<typename T>
concept ChampionConcept=requires{
    T::BaseADLv1;
    T::ADGrowth;
    T::BaseAttackSpeed;
    T::AttackSpeedRatio;
    T::AttackSpeedGrowth;
    T::BaseHPLv1;
    T::HPGrowth;
    T::BaseArmorLv1;
    T::ArmorGrowth;
    T::BaseMRLv1;
    T::MRGrowth;
};

template<typename T>
concept StatConcept=std::derived_from<T,Stat>;

class Skill;
class ChampionSkill;
class Item;

template<typename T>
concept SkillConcept=std::derived_from<T,Skill>;
template<typename T>
concept ChampionSkillConcept=std::derived_from<T,ChampionSkill>;
template<typename T>
concept ItemConcept=std::derived_from<T,Item>;


#endif //PA_PROJ_CONCEPTS_H
