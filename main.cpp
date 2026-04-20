// main.cpp
// Demonstrates all features of TrafficSignal Library

#include <iostream>
#include "TrafficSignal.h"
using namespace std;

void printHeader(string title) {
    cout << "\n======================================\n";
    cout << "  " << title << "\n";
    cout << "======================================\n";
}

int main() {

    // ─────────────────────────────────────────
    // SECTION 1: Function Overloading (Constructors)
    // ─────────────────────────────────────────
    printHeader("1. FUNCTION OVERLOADING - Constructors");

    // Default constructor
    TrafficSignal s1;
    cout << "\n[Default Constructor]\n" << s1;

    // Parameterized constructor
    TrafficSignal s2("Main Boulevard", 45, 5, 30, 120);
    cout << "\n[Parameterized Constructor]\n" << s2;

    // Copy constructor
    TrafficSignal s3(s2);
    cout << "\n[Copy Constructor]\n" << s3;

    // ─────────────────────────────────────────
    // SECTION 2: Function Overloading (setTiming)
    // ─────────────────────────────────────────
    printHeader("2. FUNCTION OVERLOADING - setTiming()");

    TrafficSignal s4("Ring Road", 30, 5, 30, 80);
    s4.setTiming(50);           // 1 param
    s4.setTiming(40, 35);       // 2 params
    s4.setTiming(45, 6, 30);    // 3 params
    cout << s4;

    // ─────────────────────────────────────────
    // SECTION 3: Operator Overloading
    // ─────────────────────────────────────────
    printHeader("3. OPERATOR OVERLOADING");

    TrafficSignal roadA("GT Road", 40, 5, 35, 150);
    TrafficSignal roadB("Jail Road", 30, 5, 45, 90);

    roadA.setState("GREEN");
    roadB.setState("RED");

    // + operator
    cout << "\n[+ Operator: Merged Intersection]\n";
    TrafficSignal merged = roadA + roadB;
    cout << merged;

    // - operator
    cout << "\n[- Operator: Remove 50 vehicles from GT Road]\n";
    TrafficSignal afterClear = roadA - 50;
    cout << afterClear;

    // * operator
    cout << "\n[* Operator: Scale timings by 1.5x (rush hour)]\n";
    TrafficSignal rushHour = roadA * 1.5;
    cout << rushHour;

    // == operator
    cout << "\n[== Operator: Do roadA and roadB have same timings?]\n";
    if (roadA == roadB)
        cout << "  YES — Same signal timings.\n";
    else
        cout << "  NO  — Different signal timings.\n";

    // < and > operators
    cout << "\n[< and > Operators: Congestion Comparison]\n";
    if (roadA > roadB)
        cout << "  " << roadA.getRoadName() << " is MORE congested ("
        << roadA.getVehicleCount() << " vehicles).\n";
    else
        cout << "  " << roadB.getRoadName() << " is MORE congested ("
        << roadB.getVehicleCount() << " vehicles).\n";

    // ─────────────────────────────────────────
    // SECTION 4: Simulation Scenario
    // ─────────────────────────────────────────
    printHeader("4. MINI SIMULATION SCENARIO");

    TrafficSignal intersection("City Center", 30, 5, 30, 200);
    intersection.setState("RED");

    cout << "\n[Initial State]\n" << intersection;

    // Peak hour — add vehicles
    intersection.addVehicles(100);
    intersection.setState("GREEN");
    intersection.setTiming(60, 5, 20); // extend green for rush
    cout << "\n[After Peak Hour Adjustment]\n" << intersection;

    // Some vehicles clear
    intersection.removeVehicles(150);
    intersection.setState("YELLOW");
    cout << "\n[After Vehicles Clear]\n" << intersection;

    cout << "\n  Efficiency: " << intersection.efficiency() * 100 << "%\n";
    cout << "  Est. Throughput: " << intersection.throughput() << " vehicles/cycle\n";

    cout << "\n======================================\n";
    cout << "  Simulation Complete!\n";
    cout << "======================================\n";

    return 0;
}