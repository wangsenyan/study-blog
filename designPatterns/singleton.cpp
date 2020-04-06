// class Singleton {
//     public:
//         static Singleton *Instance();
//     protected:
//         Singl  eton();
//     private:
//         static Singleton *_instance;
// };
// //需要锁
// Singleton *Singleton::_instance = 0;

// Singleton *Singleton::Instance()
// {
//     if(_instance==0)
//         _instance = new Singleton;
//     return _instance;
// }

class Singleton {
    public:
        void Register(const char *name, Singleton *);
        static Singleton *Instance;
    protected:
        static Singleton *Lookup(const char *name);
    private:
        static Singleton *_instance;
        static List<NameSingletonPair> *_registry;
};

Singleton *Singleton::Instance()
{
    if(_instance==0)
    {
        const char *singletonName = getenv("SINGLETON");

        _instance = Lookup(singletonName);
    }
    return _instance;
}