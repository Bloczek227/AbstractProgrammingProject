#ifndef PA_PROJ_TWITCH_H
#define PA_PROJ_TWITCH_H
#include "../equipment.h"
#include "../champion.h"
#include "../points.h"


template<int Level, class Equipment=Equipment<>,class Points=Points<0,0,0,0>>
class Twitch:public Champion<Twitch<Level,Equipment,Points>>{
public:
    using Super=Champion<Twitch<Level,Equipment,Points>>;
    constexpr static int lv=Level;
    using eq=Equipment;
    static constexpr int QPoints=Points::QPoints;
    static constexpr int WPoints=Points::WPoints;
    static constexpr int EPoints=Points::EPoints;
    static constexpr int RPoints=Points::RPoints;

    constexpr static double BaseADLv1=59;
    constexpr static double ADGrowth=3.1;
    constexpr static double BaseAttackSpeed=0.679;
    constexpr static double AttackSpeedRatio=0.679;
    constexpr static double AttackSpeedGrowth=3.38;
    constexpr static double BaseCriticalBonusDamage=75;
    constexpr static double BaseHPLv1=682;
    constexpr static double HPGrowth=100;
    constexpr static double BaseArmorLv1=27;
    constexpr static double ArmorGrowth=4.2;
    constexpr static double BaseMRLv1=30;
    constexpr static double MRGrowth=1.3;
    constexpr static bool IsRanged=true;

    static double CurrentHP;

    static double BonusAttackSpeed(){return AttackSpeedGrowth*(lv-1)*(0.685+lv*0.0175)+eq::template ItemsStatValue<AttackSpeed>()+
                                            (35+5*QPoints)*(Q::QTicksLeft>0);}
    static double TotalAttackSpeed(){return BaseAttackSpeed+AttackSpeedRatio*BonusAttackSpeed()/100;}
    static double BonusAD(){return eq::template ItemsStatValue<AD>()+(R::RTicksLeft>0?25+15*RPoints:0);}
    static double TotalAD(){return Super::BaseAD()+BonusAD();}

    template<int TargetsHitBefore=0>
    class BasicAttack:public ChampionSkill{
    public:
        constexpr static bool onHit=true;
        constexpr static bool onAttack=true;
        constexpr static int MaxTargetsReducing=4;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static double PhysDamage(){return TotalAD()*(1+Super::TotalCriticalChance()/100*Super::TotalCriticalBonusDamage()/100)*
        (1-0.1*TargetsHitBefore*(R::RTicksLeft>0));}
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){Passive::addStack();}
    };

    class Passive:public ChampionSkill{
    public:
        static int stacks;
        constexpr static int maxStacks=6;
        constexpr static double calculatePassiveBaseDamage(){return Level<5?1:Level<9?2:Level<13?3:Level<17?4:5;}
        static int PassiveTicksLeft;

        static void addStack(){
            stacks=(PassiveTicksLeft>0?(stacks<maxStacks?(stacks+1):maxStacks):1);
            PassiveTicksLeft=6*TicksPerSecond;
        }
        class WaitTick:public ChampionSkill{
        public:
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static double TrueDamage(){
                return (PassiveTicksLeft>0)*(calculatePassiveBaseDamage()+0.03*Super::TotalAP())*stacks/Skill::TicksPerSecond;
            }
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static void use(){
                PassiveTicksLeft-=1;
            }
        };
    };

    class Q:public ChampionSkill{
    public:
        static int QTicksLeft;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            QTicksLeft=5*TicksPerSecond;
        }
        class WaitTick:public ChampionSkill{
        public:
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static void use(){
                QTicksLeft-=1;
            }
        };
    };

    class W:public ChampionSkill{
    public:
        static int WTicksLeft;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            WTicksLeft=3*TicksPerSecond;
            Passive::addStack();
        }
        class WaitTick:public ChampionSkill{
        public:
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static void use(){
                Passive::stacks=WTicksLeft%TicksPerSecond!=1?Passive::stacks:
                        (Passive::PassiveTicksLeft>0?(Passive::stacks<Passive::maxStacks?(Passive::stacks+1):Passive::maxStacks):1);
                Passive::PassiveTicksLeft==WTicksLeft%TicksPerSecond!=1?Passive::PassiveTicksLeft:6*TicksPerSecond;
                WTicksLeft-=1;
            }
        };
    };

    class E:public ChampionSkill{
    public:
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){}
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static double PhysDamage(){
            return (Passive::PassiveTicksLeft>0)*(10+10*QPoints+(10+5*QPoints+0.35*BonusAD())*Passive::stacks);
        }
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static double MagicDamage(){
            return (Passive::PassiveTicksLeft>0)*0.3*Super::TotalAP()*Passive::stacks;
        }
    };


    class R:public ChampionSkill{
    public:
        static int RTicksLeft;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            RTicksLeft=6*TicksPerSecond;
        }
        class WaitTick:public ChampionSkill{
        public:
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static void use(){
                RTicksLeft-=1;
            }
        };
    };


    using WaitTick=ChampionSkillSum<ChampionSkillSum<typename Passive::WaitTick,typename Q::WaitTick>,
            ChampionSkillSum<typename W::WaitTick,typename R::WaitTick>>;
    static void reset(){
        CurrentHP=Super::TotalHP();
        Passive::PassiveTicksLeft=0;
        Passive::stacks=0;
        Q::QTicksLeft=0;
        W::WTicksLeft=0;
        R::RTicksLeft=0;
        Equipment::template reset<Twitch<Level,Equipment,Points>>();
    }
};
template<int Level,class Equipment, class Points> double Twitch<Level,Equipment,Points>::CurrentHP=Twitch<Level,Equipment,Points>::TotalHP();
template<int Level,class Equipment, class Points> int Twitch<Level,Equipment,Points>::Passive::stacks=0;
template<int Level,class Equipment, class Points> int Twitch<Level,Equipment,Points>::Passive::PassiveTicksLeft=0;
template<int Level,class Equipment, class Points> int Twitch<Level,Equipment,Points>::Q::QTicksLeft=0;
template<int Level,class Equipment, class Points> int Twitch<Level,Equipment,Points>::W::WTicksLeft=0;
template<int Level,class Equipment, class Points> int Twitch<Level,Equipment,Points>::R::RTicksLeft=0;
#endif //PA_PROJ_TWITCH_H
