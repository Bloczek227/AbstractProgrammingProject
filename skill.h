#ifndef PA_PROJ_SKILL_H
#define PA_PROJ_SKILL_H

#include "concepts.h"

class Skill{
public:
    constexpr static int TicksPerSecond=10;
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double PhysDamage(){return 0;}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double MagicDamage(){return 0;}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double TrueDamage(){return 0;}
};
template<ChampionConcept OffensiveChamp>
class ZeroSkill:public Skill{};
class ChampionSkill:public Skill{
public:
    constexpr static bool onHit=false;
    constexpr static bool onAttack=false;
    constexpr static bool ability=false;
    constexpr static int dashRange=0;
};

template<ChampionConcept OffensiveChamp>
class ItemSkill:public Skill{};

template<SkillConcept Skill1,SkillConcept Skill2>
class SkillSum:public Skill{
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double PhysDamage(){return Skill1::template PhysDamage<DefendingChamp,ChampionSkill>()+Skill2::template PhysDamage<DefendingChamp,ChampionSkill>();}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double TrueDamage(){return Skill1::template TrueDamage<DefendingChamp,ChampionSkill>()+Skill2::template TrueDamage<DefendingChamp,ChampionSkill>();}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double MagicDamage(){return Skill1::template MagicDamage<DefendingChamp,ChampionSkill>()+Skill2::template MagicDamage<DefendingChamp,ChampionSkill>();}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){Skill1::template use<DefendingChamp,ChampionSkill>();Skill2::template use<DefendingChamp,ChampionSkill>();}
};
template<ChampionSkillConcept Skill1,ChampionSkillConcept Skill2>
class ChampionSkillSum:public ChampionSkill{
public:
    constexpr static bool onHit=Skill1::onHit||Skill2::onHit;
    constexpr static bool onAttack=Skill1::onAttack||Skill2::onAttack;
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double PhysDamage(){return Skill1::template PhysDamage<DefendingChamp,ChampionSkill>()+Skill2::template PhysDamage<DefendingChamp,ChampionSkill>();}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double TrueDamage(){return Skill1::template TrueDamage<DefendingChamp,ChampionSkill>()+Skill2::template TrueDamage<DefendingChamp,ChampionSkill>();}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double MagicDamage(){return Skill1::template MagicDamage<DefendingChamp,ChampionSkill>()+Skill2::template MagicDamage<DefendingChamp,ChampionSkill>();}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){Skill1::template use<DefendingChamp,ChampionSkill>();Skill2::template use<DefendingChamp,ChampionSkill>();}
};

#endif //PA_PROJ_SKILL_H
