#ifndef PA_PROJ_DRAVEN_H
#define PA_PROJ_DRAVEN_H

#include "../equipment.h"
#include "../champion.h"
#include "../points.h"


template<int Level, class Equipment=Equipment<>,class Points=Points<0,0,0,0>>
class Draven:public Champion<Draven<Level,Equipment,Points>>{
public:
    using Super=Champion<Draven<Level,Equipment,Points>>;
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
    constexpr static bool IsRanged=true;

    static double CurrentHP;

    static double BonusAttackSpeed(){return AttackSpeedGrowth*(lv-1)*(0.685+lv*0.0175)+eq::template ItemsStatValue<AttackSpeed>()+
                                            (15+5*WPoints)*(W::WTicksLeft>0);}
    static double TotalAttackSpeed(){return BaseAttackSpeed+AttackSpeedRatio*BonusAttackSpeed()/100;}

    class BasicAttack:public ChampionSkill{
    public:
        constexpr static bool onHit=true;
        constexpr static bool onAttack=true;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static double PhysDamage(){return Super::TotalAD()*(1+Super::TotalCriticalChance()/100*Super::TotalCriticalBonusDamage()/100)+
                    (Q::axes>0)*(35+5*QPoints+(0.65+0.1*QPoints)*Super::BonusAD());}
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            Q::axes=Q::axes>0?Q::axes-1:0;
            Q::QTicksLeft=Q::axes>0?58*TicksPerSecond/10:0;
        }
    };

    class Passive:public ChampionSkill{
    public:
        static int stacks;
    };

    class Q:public ChampionSkill{
    public:
        constexpr static bool ability=true;
        static int QTicksLeft;
        static int axes;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            QTicksLeft=58*TicksPerSecond/10;
            axes=axes>=2?2:axes+1;
        }
        static void grabAxe(){
            QTicksLeft=58*TicksPerSecond/10;
            axes=axes>=2?2:axes+1;
            Passive::stacks++;
        }
        class WaitTick:public ChampionSkill{
        public:
            template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
            static void use(){
                QTicksLeft-=1;
                axes=QTicksLeft<=0?0:axes;
            }
        };
    };

    class W:public ChampionSkill{
    public:
        constexpr static bool ability=true;
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
        constexpr static bool ability=true;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static double PhysDamage(){return 40+35*EPoints+0.5*Super::BonusAD();}
    };


    template<int TargetsHitBefore=0>
    class R:public ChampionSkill{
    public:
        constexpr static bool ability=true;
        static int RTicksLeft;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static double PhysDamage(){
            return TargetsHitBefore<6?(75+100*RPoints+(0.9+0.2*RPoints)*Super::BonusAD())*(1-0.1*TargetsHitBefore):
            (75+100*RPoints+(0.9+0.2*RPoints)*Super::BonusAD())*0.4;
        }
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            DefendingChamp::CurrentHP=DefendingChamp::CurrentHP>Passive::stacks?DefendingChamp::CurrentHP:0;
        }
    };


    using WaitTick=ChampionSkillSum<typename Q::WaitTick,typename W::WaitTick>;
    static void reset(){
        CurrentHP=Super::TotalHP();
        Passive::stacks=0;
        Q::QTicksLeft=0;
        Q::axes=0;
        W::WTicksLeft=0;
        Equipment::template reset<Draven<Level,Equipment,Points>>();
    }
};
template<int Level,class Equipment, class Points> int Draven<Level,Equipment,Points>::Passive::stacks=0;
template<int Level,class Equipment, class Points> double Draven<Level,Equipment,Points>::CurrentHP=Draven<Level,Equipment,Points>::TotalHP();
template<int Level,class Equipment, class Points> int Draven<Level,Equipment,Points>::Q::QTicksLeft=0;
template<int Level,class Equipment, class Points> int Draven<Level,Equipment,Points>::Q::axes=0;
template<int Level,class Equipment, class Points> int Draven<Level,Equipment,Points>::W::WTicksLeft=0;

#endif //PA_PROJ_DRAVEN_H
