class Equipment {
    public:
        ~Equipment();
        const char *Name() { return _name; }
        virtual Watt Power();
        virtual Currency NetPrice();
        virtual Currency DiscountPrice();
        virtual void Add(Equipment *);
        virtual void Remove(Equipment *);
        virtual Iterator<Equipment *> *CreateIterator();
    protected:
        Equipment(const char *);
    private:
        const char *_name;
};

class FloppyDisk:public Equipment {
    public:
        FloppyDisk(const char *);
        virtual ~FloppyDisk();
        virtual Watt Power();
        virtual Currency NetPrice();
        virtual Currency DiscountPrice();
};

class CompositeEquipment:public Equipment {
    public:
        virtual ~CompositeEquipment();
        virtual Watt Power();
        virtual Currency NetPrice();
        virtual Currency DiscountPrice();

        virtual void Add(Equipment *);
        virtual void Remove(Equipment *);
        virtual Iterator<Equipment *> *CreateIterator();
    protected:
        CompositeEquipment(const char *);
    private:
        List<Equipment *> _equipment;
};

Currency CompositeEquipment::NetPrice()
{
    Iterator<Equipment *> *i = CreateIterator();
    Currency total = 0;
    for (i->First(); !i->IsDone;i->Next()){
        total += i->CurrenctItem()->NetPrice();
    }
    delete i;
    return total;
}