/* calcul.x : utilisation de rpcgen */

struct Param {
    long base;
    long exponent;
};

program CAL_BIN_PROG {
    version CAL_VERS_ONE {
        void CALNULL(void) = 0;
        long int PUISS(struct Param) = 1;
        long int DEC2BIN(int) = 2;
    } = 1;
} = 0x20000001;

