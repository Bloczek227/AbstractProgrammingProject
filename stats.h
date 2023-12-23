#ifndef PA_PROJ_STATS_H
#define PA_PROJ_STATS_H

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

#endif //PA_PROJ_STATS_H