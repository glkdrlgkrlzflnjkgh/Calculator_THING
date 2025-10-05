#include <iostream>
#include <string>
#include <iomanip>
#include "Calculator.h"
#include "Config.h"

static_assert(sizeof(int) >= 4, "Sizeof int is not equal to, or greater than 4!");
static_assert(sizeof(double) >= 8, "Sizeof double is not equal to, or greater than 8!");

int main() {

    Calculator calc;
    std::string input;
    if (debug) {
        std::cout << "!this is the debugging build, if you see this message in a public build. QUIT. NOW!" << std::endl;
    }
    
    std::cout << "WARNING: this app is NOT ready to be used in scenarios such as: \n dosage calculations for medical devices, aerospace simulations, and safety-critical systems! \n YOU HAVE BEEN WARNED!" << std::endl;
	std::cout << "Decompilation or reverse engineering is prohibited,\n except for strictly private educational purposes where no code, \n logic, or derivative work is redistributed, published, or used commercially." << std::endl;
    std::cout << "THIS SOFTWARE IS PROVIDED AS-IS, WITHOUT WARRANTY OF ANY KIND. USE AT YOUR OWN RISK." << std::endl;
    std::cout << "=== CLI Calculator === version: " << version << "," << " built on: " << build_date << "," << " at time: " << build_time << std::endl;
    std::cout << "Copyright Callum Nicoll 2025, all rights reserved." << std::endl;
    std::cout << "Type 'exit' or 'q' to quit." << std::endl;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "no input" << std::endl;
            continue;
		}
        if (input == "exit" || input == "q") {
            std::cout << "Quitting..." << std::endl;
            break;
        }
        if (input == "legal") {
            std::cout << "WARNING: this app is NOT ready to be used in scenarios such as: \n dosage calculations for medical devices, aerospace simulations, and safety-critical systems! \n YOU HAVE BEEN WARNED!" << std::endl;
            std::cout << "Decompilation or reverse engineering is prohibited,\n except for strictly private educational purposes where no code, \n logic, or derivative work is redistributed, published, or used commercially." << std::endl;
            std::cout << "THIS SOFTWARE IS PROVIDED AS-IS, WITHOUT WARRANTY OF ANY KIND. USE AT YOUR OWN RISK." << std::endl;
            std::cout << "Copyright Callum Nicoll 2025, all rights reserved." << std::endl;
            continue;
        }
        if (input == "source-code") {
            std::cout << "the source code of this software is not publically on the internet, if you have any questions, contact the developer at: xcallumnicx@outlook.com" << std::endl;
            continue;
        }

        try {
            double result = calc.evaluate(input);
            std::cout << std::fixed << std::setprecision(8);
            std::cout << "Result: " << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}