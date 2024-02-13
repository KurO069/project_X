struct user
{
    int _id;
    char _name[20][2];
    char _addr[30];
    char _email[30];
    char _pass[30];
};

struct electricity
{
    int _id;
    int _prevReading;
    int _due;
    int _advance;
};

struct water
{
    int _id;
    int _prevReading;
    int _due;
    int _advance;
};

struct tax
{
    int _id;
    int _yearlyIncome;
    int _due;
    int _advance;
};
struct call
{
    int _id;
    int _due;
    int _advance;
};