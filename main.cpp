#include <iostream>

class Stat{};
class AdditiveStat:public Stat{
public:
    constexpr static double baseValue=0;
    static double StackingMethod(double x, double y){return x+y;}
};
class MultiplicativeStat:public Stat{
public:
    constexpr static double baseValue=1;
};
class MultiplicativePercentageStat:public Stat{
public:
    constexpr static double baseValue=0;
};
class MultiplicativeIncreasingStat:public MultiplicativeStat{
public:
    static double StackingMethod(double x, double y){return x*y;}
};
class MultiplicativeDecreasingStat:public MultiplicativePercentageStat{
public:
    static double StackingMethod(double x, double y){return 100-((100-x)*(100-y))/100;}
};
class AD:public AdditiveStat{};
class AttackSpeed:public AdditiveStat{};
class CriticalChance:public AdditiveStat{};
class CriticalBonusDamage:public AdditiveStat{};
class Lethality:public AdditiveStat{};
class ArmorPenetration:public MultiplicativeDecreasingStat{};
class AP:public AdditiveStat{};
class APMultiplier:public MultiplicativeIncreasingStat{};
class FlatMagicPenetration:public AdditiveStat{};
class PercentageMagicPenetration:public MultiplicativeDecreasingStat{};
class HP:public AdditiveStat{};
class Armor:public AdditiveStat{};
class MagicResist:public AdditiveStat{};

constexpr double calculateReluFunction(double baseValue,int firstChangeLevel,int changeValue,int level){
    return level<firstChangeLevel?baseValue:(level-firstChangeLevel+1)*changeValue;
}


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

template<class Champ>
class Champion{
public:
    static double BaseAD() {return Champ::BaseADLv1+Champ::ADGrowth*(Champ::lv-1)*(0.685+Champ::lv*0.0175);}
    static double BaseHP() {return Champ::BaseHPLv1+Champ::HPGrowth*(Champ::lv-1)*(0.685+Champ::lv*0.0175);}
    static double BaseArmor() {return Champ::BaseArmorLv1+Champ::ArmorGrowth*(Champ::lv-1)*(0.685+Champ::lv*0.0175);}
    static double BaseMR() {return Champ::BaseMRLv1+Champ::MRGrowth*(Champ::lv-1)*(0.685+Champ::lv*0.0175);}

    static double BonusAD(){return Champ::eq::template ItemsStatValue<AD>();}
    static double BonusAttackSpeed(){return Champ::AttackSpeedGrowth*(Champ::lv-1)*(0.685+Champ::lv*0.0175)+Champ::eq::template ItemsStatValue<AttackSpeed>();}
    static double BonusHP(){return Champ::eq::template ItemsStatValue<HP>();}
    static double BonusArmor(){return Champ::eq::template ItemsStatValue<Armor>();}
    static double BonusMR(){return Champ::eq::template ItemsStatValue<MagicResist>();}

    static double TotalAD(){return BaseAD()+BonusAD();}
    static double TotalAttackSpeed(){return Champ::BaseAttackSpeed+Champ::AttackSpeedRatio*BonusAttackSpeed()/100;}
    static double TotalCriticalChance(){return Champ::eq::template ItemsStatValue<CriticalChance>();}
    static double TotalCriticalBonusDamage(){return Champ::BaseCriticalBonusDamage+Champ::eq::template ItemsStatValue<CriticalBonusDamage>();}
    static double TotalLethality(){return Champ::eq::template ItemsStatValue<Lethality>();}
    static double TotalArmorPenetration(){return Champ::eq::template ItemsStatValue<ArmorPenetration>();}
    static double TotalHP(){return BaseHP()+BonusHP();}
    static double TotalAP(){return Champ::eq::template ItemsStatValue<AP>()*Champ::eq::template ItemsStatValue<APMultiplier>();}
    static double TotalFlatMagicPenetration(){return Champ::eq::template ItemsStatValue<FlatMagicPenetration>();}
    static double TotalPercentageMagicPenetration(){return Champ::eq::template ItemsStatValue<PercentageMagicPenetration>();}
    static double TotalArmor(){return BaseArmor()+BonusArmor();}
    static double TotalMR(){return BaseMR()+BonusMR();}

    static double DamageReceived(){return Champ::TotalHP()-Champ::CurrentHP;};
};


template<typename T>
concept StatConcept=std::derived_from<T,Stat>;

class Skill;
class ChampionSkill;

template<typename T>
concept SkillConcept=std::derived_from<T,Skill>;
template<typename T>
concept ChampionSkillConcept=std::derived_from<T,ChampionSkill>;

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


class Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
};
template<typename T>
concept ItemConcept=std::derived_from<T,Item>;

class LongSword: public Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double LongSword::StatValue<AD>(){return 10;}

template<ChampionConcept OffensiveChamp>
class RecurveBowPassive:public ItemSkill<OffensiveChamp>{
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double MagicDamage(){return ChampionSkill::onHit*15;}
};
class RecurveBow: public Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=RecurveBowPassive<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double RecurveBow::StatValue<AttackSpeed>(){return 15;}

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


class InfinityEdge: public Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double InfinityEdge::StatValue<AD>(){return 65;}
template<> double InfinityEdge::StatValue<CriticalChance>(){return 20;}
template<> double InfinityEdge::StatValue<CriticalBonusDamage>(){return 40;}


class YoumuusGhostblade: public Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double YoumuusGhostblade::StatValue<AD>(){return 60;}
template<> double YoumuusGhostblade::StatValue<Lethality>(){return 18;}


template<ChampionConcept OffensiveChamp>
class TheCollectorPassive:public ItemSkill<OffensiveChamp>{
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){
        DefendingChamp::CurrentHP=DefendingChamp::CurrentHP/DefendingChamp::TotalHP()>0.05?DefendingChamp::CurrentHP:0;
    }
};
class TheCollector: public Item{
public:
    template<StatConcept Stat> static double StatValue(){return Stat::baseValue;};
    template<ChampionConcept OffensiveChamp>
    using SkillType=ZeroSkill<OffensiveChamp>;
    template<ChampionConcept OffensiveChamp> static void reset(){}
};
template<> double TheCollector::StatValue<AD>(){return 60;}
template<> double TheCollector::StatValue<CriticalChance>(){return 20;}
template<> double TheCollector::StatValue<Lethality>(){return 16;}



template<ItemConcept...Items>
class Equipment{
public:
    template<StatConcept Stat>
    static double ItemsStatValue(){return Stat::baseValue;}
    template<ChampionConcept OffensiveChamp>
    using SkillType=Skill;
    template<ChampionConcept OffensiveChamp>
    static void reset(){}
};
template<ItemConcept FirstItem,ItemConcept... NextItems>
class Equipment<FirstItem,NextItems...>{
public:
    template<StatConcept Stat>
    static double ItemsStatValue(){return Stat::StackingMethod(FirstItem::template StatValue<Stat>(),Equipment<NextItems...>::template ItemsStatValue<Stat>());}
    template<ChampionConcept OffensiveChamp>
    using SkillType=SkillSum<typename FirstItem::template SkillType<OffensiveChamp>,typename Equipment<NextItems...>::template SkillType<OffensiveChamp>>;
    template<ChampionConcept OffensiveChamp>
    static void reset(){FirstItem::template reset<OffensiveChamp>();Equipment<NextItems...>::template reset<OffensiveChamp>();}
};

template<int Q,int W,int E,int R>
class Points{
public:
    static constexpr int QPoints=Q;
    static constexpr int WPoints=W;
    static constexpr int EPoints=E;
    static constexpr int RPoints=R;
};


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

template<class Fight,SkillConcept ChampionSkill,int Ticks>
class WaitTicks{
public:
    static void tick(){
        using result=Fight::off::WaitTick;
        double flatDamage=result::template PhysDamage<typename Fight::def,ChampionSkill>()*
                                ((Fight::def::TotalArmor()*(1-Fight::off::TotalArmorPenetration()/100)-Fight::off::TotalLethality()>0)?
                                (100/(100+Fight::def::TotalArmor()*(1-Fight::off::TotalArmorPenetration()/100)-Fight::off::TotalLethality())):
                                (2-100/(100-Fight::def::TotalArmor()*(1-Fight::off::TotalArmorPenetration()/100)+Fight::off::TotalLethality())))+
                          result::template MagicDamage<typename Fight::def,ChampionSkill>()*
                                  ((Fight::def::TotalMR()*(1-Fight::off::TotalPercentageMagicPenetration()/100)-Fight::off::TotalFlatMagicPenetration()>0)?
                                   (100/(100+Fight::def::TotalMR()*(1-Fight::off::TotalPercentageMagicPenetration()/100)-Fight::off::TotalFlatMagicPenetration())):
                                   1)+
                          result::template TrueDamage<typename Fight::def,ChampionSkill>();
        Fight::def::CurrentHP-=flatDamage;
        Fight::def::CurrentHP=Fight::def::CurrentHP>0?Fight::def::CurrentHP:0;
        result::template use<typename Fight::def,ChampionSkill>();
        WaitTicks<Fight,ChampionSkill,Ticks-1>::tick();
    }
};
template<class Fight, SkillConcept ChampionSkill>
class WaitTicks<Fight,ChampionSkill,0> {
public:
    static void tick(){};
};

template<ChampionConcept OffensiveChamp,ChampionConcept DefendingChamp>
class Fight{
public:
    using off=OffensiveChamp;
    using def=DefendingChamp;
    template<ChampionSkillConcept ChampionSkill>
    static void UseSkill(){
        using result=SkillSum<ChampionSkill,typename OffensiveChamp::eq:: template SkillType<OffensiveChamp>>;
        double flatDamage=result::template PhysDamage<DefendingChamp,ChampionSkill>()*
                                  ((DefendingChamp::TotalArmor()*(1-OffensiveChamp::TotalArmorPenetration()/100)-OffensiveChamp::TotalLethality()>0)?
                                   (100/(100+DefendingChamp::TotalArmor()*(1-OffensiveChamp::TotalArmorPenetration()/100)-OffensiveChamp::TotalLethality())):
                                   (2-100/(100-DefendingChamp::TotalArmor()*(1-OffensiveChamp::TotalArmorPenetration()/100)+OffensiveChamp::TotalLethality())))+
                result::template MagicDamage<DefendingChamp,ChampionSkill>()*
                ((DefendingChamp::TotalMR()*(1-OffensiveChamp::TotalPercentageMagicPenetration()/100)-OffensiveChamp::TotalFlatMagicPenetration()>0)?
                 (100/(100+DefendingChamp::TotalMR()*(1-OffensiveChamp::TotalPercentageMagicPenetration()/100)-OffensiveChamp::TotalFlatMagicPenetration())):
                 1)+
                result::template TrueDamage<DefendingChamp,ChampionSkill>();
        DefendingChamp::CurrentHP-=flatDamage;
        DefendingChamp::CurrentHP=DefendingChamp::CurrentHP>0?DefendingChamp::CurrentHP:0;
        result::template use<DefendingChamp,ChampionSkill>();
    }

    template<int Ticks>
    static void waitTicks(){
        WaitTicks<Fight,typename off::WaitTick,Ticks>::tick();
    }
    static void reset(){
        Fight::off::reset();
        Fight::def::reset();
    }
};






int main() {
    using MF1=MissFortune<8,Equipment<LongSword,KrakenSlayer>,Points<4,1,2,1>>;
    using MF2=MissFortune<9,Equipment<KrakenSlayer>,Points<5,1,2,1>>;
    using fight=Fight<MF1,MF2>;
    fight::UseSkill<MF1::BasicAttack>();
    fight::UseSkill<MF1::Q<>>();
    fight::UseSkill<MF1::BasicAttack>();
    std::cout <<fight::def::DamageReceived()<< std::endl;
    fight::reset();

    fight::UseSkill<MF1::W>();
    fight::UseSkill<MF1::E>();
    fight::UseSkill<MF1::BasicAttack>();
    fight::UseSkill<MF1::Q<1>>();
    fight::waitTicks<10>();
    fight::UseSkill<MF1::BasicAttack>();
    fight::UseSkill<MF1::R>();
    fight::waitTicks<10>();
    std::cout <<fight::def::DamageReceived()<< std::endl<<std::endl;
    fight::reset();


    using MF3=MissFortune<8,Equipment<InfinityEdge>,Points<4,1,2,1>>;
    using fight2=Fight<MF3,MF2>;
    fight2::UseSkill<MF3::BasicAttack>();
    fight2::UseSkill<MF3::Q<>>();
    fight2::UseSkill<MF3::BasicAttack>();
    std::cout <<fight2::def::DamageReceived()<< std::endl;
    fight2::reset();

    fight2::UseSkill<MF3::W>();
    fight2::UseSkill<MF3::E>();
    fight2::UseSkill<MF3::BasicAttack>();
    fight2::UseSkill<MF3::Q<1>>();
    fight2::waitTicks<10>();
    fight2::UseSkill<MF3::BasicAttack>();
    fight2::UseSkill<MF3::R>();
    fight2::waitTicks<10>();
    std::cout <<fight2::def::DamageReceived()<< std::endl<<std::endl;
    fight2::reset();





    using MF4=MissFortune<8,Equipment<YoumuusGhostblade,LongSword,LongSword>,Points<4,1,2,1>>;
    using fight3=Fight<MF4,MF2>;
    fight3::UseSkill<MF4::BasicAttack>();
    fight3::UseSkill<MF4::Q<>>();
    fight3::UseSkill<MF4::BasicAttack>();
    std::cout <<fight3::def::DamageReceived()<< std::endl;
    fight3::reset();

    fight3::UseSkill<MF4::W>();
    fight3::UseSkill<MF4::E>();
    fight3::UseSkill<MF4::BasicAttack>();
    fight3::UseSkill<MF4::Q<1>>();
    fight3::waitTicks<10>();
    fight3::UseSkill<MF4::BasicAttack>();
    fight3::UseSkill<MF4::R>();
    fight3::waitTicks<10>();
    std::cout <<fight3::def::DamageReceived()<< std::endl<<std::endl;
    fight3::reset();



    using MF5=MissFortune<8,Equipment<TheCollector,LongSword>,Points<4,1,2,1>>;
    using fight4=Fight<MF5,MF2>;
    fight4::UseSkill<MF5::BasicAttack>();
    fight4::UseSkill<MF5::Q<>>();
    fight4::UseSkill<MF5::BasicAttack>();
    std::cout <<fight4::def::DamageReceived()<< std::endl;
    fight4::reset();

    fight4::UseSkill<MF5::W>();
    fight4::UseSkill<MF5::E>();
    fight4::UseSkill<MF5::BasicAttack>();
    fight4::UseSkill<MF5::Q<1>>();
    fight4::waitTicks<10>();
    fight4::UseSkill<MF5::BasicAttack>();
    fight4::UseSkill<MF5::R>();
    fight4::waitTicks<10>();
    std::cout <<fight4::def::DamageReceived()<< std::endl<<std::endl;
    fight4::reset();
    return 0;
}
