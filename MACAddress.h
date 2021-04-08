class MACAddress{
    // 12 digit hex = 12 chars = 48 bit value
    // or just put it in an int64

    public:
        MACAddress();
        ~MACAddress();
    private:
        long long int address;

};