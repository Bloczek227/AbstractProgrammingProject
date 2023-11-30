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
class MultiplicativeIncreasingStat:public MultiplicativeStat{
public:
    static double StackingMethod(double x, double y){return x*y;}
};
class MultiplicativeDecreasingStat:public MultiplicativeStat{
public:
    static double StackingMethod(double x, double y){return 1-((1-x)*(1-y));}
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
    static double TotalAD(){return BaseAD()+BonusAD();}
    static double TotalAttackSpeed(){return Champ::BaseAttackSpeed+Champ::AttackSpeedRatio*BonusAttackSpeed()/100;}
    static double TotalCriticalChance(){return Champ::eq::template ItemsStatValue<CriticalChance>();}
    static double TotalCriticalBonusDamage(){return Champ::BaseCriticalBonusDamage+Champ::eq::template ItemsStatValue<CriticalBonusDamage>();}
    static double TotalHP(){return BaseHP()+BonusHP();}
    static double TotalAP(){return Champ::eq::template ItemsStatValue<AP>()*Champ::eq::template ItemsStatValue<APMultiplier>();}
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
    static int amplifies;
public:
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static double TrueDamage(){return (counter==2&&(ChampionSkill::onHit||ChampionSkill::onAttack))*
        (calculateReluFunction(35,9,5,OffensiveChamp::lv)+0.65*OffensiveChamp::TotalAD()+0.6*OffensiveChamp::TotalAP())*
        (1+0.5*amplifies);}
    template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
    static void use(){
        counter=(counter+(ChampionSkill::onHit||ChampionSkill::onAttack))%3;
        amplifies=amplifies+(counter==0);
        amplifies=amplifies>2?2:amplifies;
    }
    static void reset(){
        counter=0;
        amplifies=0;
    }
};
template<ChampionConcept OffensiveChamp> int KrakenSlayerPassive<OffensiveChamp>::counter=0;
template<ChampionConcept OffensiveChamp> int KrakenSlayerPassive<OffensiveChamp>::amplifies=0;
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


template<int Level, class Equipment=Equipment<>>
class MissFortune:public Champion<MissFortune<Level,Equipment>>{
public:
    using Super=Champion<MissFortune<Level,Equipment>>;
    constexpr static int lv=Level;
    using eq=Equipment;
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
    template<int Points,int UseMethod=0>
    class Q:public ChampionSkill{
    public:
        constexpr static bool onHit=true;
        constexpr static bool onAttack=true;
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static double PhysDamage(){
            return (20+25*Points+1.0*Super::TotalAD()+0.35*Super::TotalAP()+Passive::PhysDamage())*
                   (1+(UseMethod==2?Super::TotalCriticalChance():UseMethod==3?100:0)/100)*Super::TotalCriticalBonusDamage()/100;
        }
        template<ChampionConcept DefendingChamp, ChampionSkillConcept ChampionSkill>
        static void use(){
            Passive::used=Passive::used&&UseMethod<2;
            Passive::use();
            Passive::used=Passive::used&&UseMethod!=1;
        }
    };
    static void reset(){
        CurrentHP=Super::TotalHP();
        Passive::used=false;
        Equipment::template reset<MissFortune<Level,Equipment>>();
    }
};
template<int Level,class Equipment> bool MissFortune<Level,Equipment>::Passive::used=false;
template<int Level,class Equipment> double MissFortune<Level,Equipment>::CurrentHP=MissFortune<Level,Equipment>::TotalHP();

template<ChampionConcept OffensiveChamp,ChampionConcept DefendingChamp>
class Fight{
public:
    using off=OffensiveChamp;
    using def=DefendingChamp;
    template<SkillConcept ChampionSkill>
    static void UseSkill(){
        using result=SkillSum<ChampionSkill,typename OffensiveChamp::eq:: template SkillType<OffensiveChamp>>;
        double flatDamage=result::template PhysDamage<DefendingChamp,ChampionSkill>()*(100/(100+DefendingChamp::BaseArmor()))+
                result::template MagicDamage<DefendingChamp,ChampionSkill>()*(100/(100+DefendingChamp::BaseMR()))+
                result::template TrueDamage<DefendingChamp,ChampionSkill>();
        DefendingChamp::CurrentHP-=flatDamage;
        result::template use<DefendingChamp,ChampionSkill>();
    }
    static void reset(){
        OffensiveChamp::reset();
        DefendingChamp::reset();
    }
};


int main() {
    using MF1=MissFortune<8,Equipment<RecurveBow,KrakenSlayer>>;
    using MF2=MissFortune<7,Equipment<KrakenSlayer>>;
    using fight=Fight<MF1,MF2>;
    fight::UseSkill<MF1::BasicAttack>();
    fight::UseSkill<MF1::Q<3>>();
    fight::UseSkill<MF1::BasicAttack>();
    std::cout <<fight::def::DamageReceived()<< std::endl;
    fight::reset();
    fight::UseSkill<MF1::BasicAttack>();
    fight::UseSkill<MF1::Q<3,1>>();
    fight::UseSkill<MF1::BasicAttack>();
    std::cout <<fight::def::DamageReceived()<< std::endl;
    return 0;
}
