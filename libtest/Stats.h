
#ifndef __NAM_TEST_STATS_H__
#define __NAM_TEST_STATS_H__

struct Stats
{
    union
    {
        struct
        {
            int strength;
            int dexterity;
            int constitution;
            int inteligence;
            int wisdom;
            int charisma;
            int luck;
            int maxHP;
            int maxMoves;
            int maxMana;
        };
        int stats[10]; // must match the number of stats above
    };
    
    void Generate() 
    {
    }
};

#endif
