#include <systemc.h>

SC_MODULE(Counter) {
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_out<sc_uint<4>> count_out;

    sc_uint<4> count;

    void counter_process() {
        if (reset.read() == 1) {
            count = 0;
        } else if (clk.posedge()) {
            count = count + 1;
        }
        count_out.write(count);
        cout << "Contador: " << count << endl; // Saída de impressão
    }

    SC_CTOR(Counter) {
        SC_METHOD(counter_process);
        sensitive << clk.pos() << reset;
    }
};

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> clk;
    sc_signal<bool> reset;
    sc_signal<sc_uint<4>> count_out;

    Counter counter("Counter");
    counter.clk(clk);
    counter.reset(reset);
    counter.count_out(count_out);

    sc_start(1, SC_NS); // inicializa a simulação

    // Teste simples: simula 10 ciclos de clock
    for (int i = 0; i < 10; i++) {
        clk = 0;
        reset = 0;
        sc_start(1, SC_NS);

        clk = 1;
        sc_start(1, SC_NS);
    }

    return 0;
}
