#ifndef PA_PROJ_CHAMPION_H
#define PA_PROJ_CHAMPION_H

#include "stats.h"

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

#endif //PA_PROJ_CHAMPION_H
