class Factory {
public:
    Factory();
    virtual ~Factory();

    static Product* createProduct (string proname);
};


