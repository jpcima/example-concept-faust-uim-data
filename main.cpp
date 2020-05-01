#include <faust/dsp/dsp.h>
#include <faust/gui/UI.h>
#include <faust/gui/meta.h>

#define FAUST_UIMACROS 1
#include "freeverb.cxx"

/*
  Example: generate UI information into static metadata
 */
struct ControlDescription {
    const char *type;
    const char *ident;
    const char *name;
    const char *var;
    float def;
    float min;
    float max;
    float step;
};

static const ControlDescription actives[] = {
    #define ACTIVE_ELEMENT(type, ident, name, var, def, min, max, step) \
        { #type, #ident, name, #var, def, min, max, step },
    FAUST_LIST_ACTIVES(ACTIVE_ELEMENT)
};
static_assert(FAUST_ACTIVES == sizeof(actives) / sizeof(actives[0]), "incorrect size of result");

/*
  Example: generate UI actives into an enum
 */
enum {
    #define ACTIVE_ENUM_MEMBER(type, ident, name, var, def, min, max, step) \
        kActive_##ident,
    FAUST_LIST_ACTIVES(ACTIVE_ENUM_MEMBER)
    //
    kNumActives,
};
static_assert(FAUST_ACTIVES == kNumActives, "incorrect size of result");

/*
 */
int main()
{
    printf(
        "=============================\n"
        "DSP Static Information (-uim)\n"
        "=============================\n"
        "\n");

    printf("Number of actives: %d\n", FAUST_ACTIVES);

    putchar('\n');

    for (int i = 0; i < FAUST_ACTIVES; ++i) {
        printf("--- active number %d\n\n", i + 1);

        printf("Parameter name:             %s\n", actives[i].name);
        printf("Kind of control:            %s\n", actives[i].type);
        printf("Unique symbol:              %s\n", actives[i].ident);
        printf("Name of instance variable:  %s\n", actives[i].var);
        putchar('\n');
        printf("Value range:                %g to %g\n", actives[i].min, actives[i].max);
        printf("Default value:              %g\n", actives[i].def);
        printf("Step:                       %g\n", actives[i].step);
        putchar('\n');
    }

    return 0;
}
