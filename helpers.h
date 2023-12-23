#ifndef PA_PROJ_HELPERS_H
#define PA_PROJ_HELPERS_H

constexpr double calculateReluFunction(double baseValue,int firstChangeLevel,int changeValue,int level){
    return level<firstChangeLevel?baseValue:(level-firstChangeLevel+1)*changeValue;
}

#endif //PA_PROJ_HELPERS_H
