#ifndef PA_PROJ_MISSFORTUNE_H
#define PA_PROJ_MISSFORTUNE_H

#include "../equipment.h"
#include "../champion.h"
#include "../points.h"


template<int Level, class Equipment=Equipment<>,class Points=Points<0,0,0,0>>
class MissFortune:public Champion<MissFortune<Level,Equipment,Points>>{
public:
    using Super=Champion<MissFortune<Level,Equipment,Points>>;
    constexpr static int lv=Level;
    using eq=Equipment;
    static constexpr int QPoints=Points::QPoints;
    static constexpr int WPoints=Points::WPoints;
    static constexpr int EPoints=Points::EPoints;
    static constexpr int RPoints=Points::RPoints;

    constexpr static double BaseADLv1=52;
    constexpr static double ADGrowth=2.4;
    constexpr static double BaseAttackSpeed=0.656;
    constexpr static double AttackSpeedRatio=0.656;
    constexpr static double AttackSpeedGrowth=3;
    constexpr static double BaseCriticalBonusDamage=75;
    constexpr static double BaseHPLv1=640;
    constexpr static double HPGrowth=103;
    constexpr static double BaseArmorLv1=28;
    constexpr static double ArmorGrowth=4.2;
    constexpr static double BaseMRLv1=30;
    constexpr static double MRGrowth=1.3;
    static double CurrentHP;

    static double BonusAttackSpeed(){return AttackSpeedGrowth*(lv-1)*(0.685+lv*0.0175)+eq::template ItemsStatValue<AttackSpeed>()+
                                            (25+15*WPoints)*(W::WTicksLeft>0);}
    constexpr static double calculatePassiveModifier(){return Level<4?0.5:Level<7?0.6:Level<9?0.7:Level<11?0.8:Level<13?0.9:1;}

    class BasicAttack:public ChampionSkill{
    public:
        constexpr static bool onHit=true;
        constexpr static bool onAttack=true;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static double PhysDamage(){return Super::TotalAD()*(1+Super::TotalCriticalChance()/100*Super::TotalCriticalBonusDamage()/100)+Passive::PhysDamage();}
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){Passive::use();}
    };

    class Passive:public ChampionSkill{
    public:
        static bool used;
        static double PhysDamage(){return (!used)*Super::TotalAD()*calculatePassiveModifier();}
        static void use(){used=true;}
    };

    //UseMethod=0 - Q used on DefendingChampion and doesn't bounce
    //UseMethod=1 - Q used on DefendingChampion and bounces
    //UseMethod=2 - Q doesn't kill first target and bounces to DefendingChampion
    //UseMethod=3 - Q kills target and bounces to DefendingChampion
    template<int UseMethod=0>
    class Q:public ChampionSkill{
    public:
        constexpr static bool onHit=true;
        constexpr static bool onAttack=true;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static double PhysDamage(){
            return (20+25*QPoints+1.0*Super::TotalAD()+0.35*Super::TotalAP()+Passive::PhysDamage())*
                   (1+(UseMethod==2?Super::TotalCriticalChance():UseMethod==3?100:0)/100)*Super::TotalCriticalBonusDamage()/100;
        }
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            Passive::used=Passive::used&&UseMethod<2;
            Passive::use();
            Passive::used=Passive::used&&UseMethod!=1;
        }
    };

    class W:public ChampionSkill{
    public:
        static int WTicksLeft;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            WTicksLeft=4*TicksPerSecond;
        }
        class WaitTick:public ChampionSkill{
        public:
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static void use(){
                WTicksLeft-=1;
            }
        };
    };

    class E:public ChampionSkill{
    public:
        static int ETicksLeft;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill,int Ticks=2*TicksPerSecond>
        static void use(){
            ETicksLeft=Ticks;
        }
        class WaitTick:public ChampionSkill{
        public:
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static double MagicDamage(){
                return (ETicksLeft>0)*(50+15*EPoints+0.6*Super::TotalAP())/Skill::TicksPerSecond;
            }
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static void use(){
                ETicksLeft-=1;
            }
        };
    };


    class R:public ChampionSkill{
    public:
        static int RTicksLeft;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            RTicksLeft=3*TicksPerSecond;
        }
        class WaitTick:public ChampionSkill{
        public:
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static double PhysDamage(){
                return (RTicksLeft>0)*(0.75*Super::TotalAD()+0.25*Super::TotalAD())*(12+RPoints)*
                       (1+(0.2+eq::template ItemsStatValue<CriticalBonusDamage>()*0.002)*Super::TotalCriticalChance()/100)/3/Skill::TicksPerSecond;
            }
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static void use(){
                RTicksLeft-=1;
            }
        };
        static void cancel(){
            RTicksLeft=0;
        }
    };



    using WaitTick=ChampionSkillSum<ChampionSkillSum<typename W::WaitTick,typename E::WaitTick>,typename R::WaitTick>;
    static void reset(){
        CurrentHP=Super::TotalHP();
        Passive::used=false;
        Equipment::template reset<MissFortune<Level,Equipment,Points>>();
    }
};
template<int Level,class Equipment, class Points> bool MissFortune<Level,Equipment,Points>::Passive::used=false;
template<int Level,class Equipment, class Points> double MissFortune<Level,Equipment,Points>::CurrentHP=MissFortune<Level,Equipment,Points>::TotalHP();
template<int Level,class Equipment, class Points> int MissFortune<Level,Equipment,Points>::W::WTicksLeft=0;
template<int Level,class Equipment, class Points> int MissFortune<Level,Equipment,Points>::E::ETicksLeft=0;
template<int Level,class Equipment, class Points> int MissFortune<Level,Equipment,Points>::R::RTicksLeft=0;
#endif //PA_PROJ_MISSFORTUNE_H
