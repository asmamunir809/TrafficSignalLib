// TrafficSignal.h
// Traffic Flow & Signal Timing Simulation Library
// Author: [Asma Munir] | Roll: [06]

#ifndef TRAFFICSIGNAL_H
#define TRAFFICSIGNAL_H

#include <iostream>
#include <string>
using namespace std;

class TrafficSignal {
private:
    string roadName;
    int greenTime;    // seconds
    int yellowTime;   // seconds
    int redTime;      // seconds
    int vehicleCount;
    string currentState; // "GREEN", "YELLOW", "RED"

public:
    // ───────────────────────────────────────────
    // FUNCTION OVERLOADING (3 constructors)
    // ───────────────────────────────────────────

    // 1. Default constructor
    TrafficSignal() {
        roadName = "Unknown Road";
        greenTime = 30;
        yellowTime = 5;
        redTime = 30;
        vehicleCount = 0;
        currentState = "RED";
    }

    // 2. Parameterized constructor
    TrafficSignal(string name, int green, int yellow, int red, int vehicles) {
        roadName = name;
        greenTime = green;
        yellowTime = yellow;
        redTime = red;
        vehicleCount = vehicles;
        currentState = "RED";
    }

    // 3. Copy constructor (overloaded form of initialization)
    TrafficSignal(const TrafficSignal& other) {
        roadName = other.roadName + "_Copy";
        greenTime = other.greenTime;
        yellowTime = other.yellowTime;
        redTime = other.redTime;
        vehicleCount = other.vehicleCount;
        currentState = other.currentState;
    }

    // ───────────────────────────────────────────
    // FUNCTION OVERLOADING: setTiming (3 versions)
    // ───────────────────────────────────────────

    // Set only green time
    void setTiming(int green) {
        greenTime = green;
        cout << "[" << roadName << "] Green time updated to " << green << "s\n";
    }

    // Set green and red time
    void setTiming(int green, int red) {
        greenTime = green;
        redTime = red;
        cout << "[" << roadName << "] Green=" << green << "s, Red=" << red << "s updated.\n";
    }

    // Set all timings
    void setTiming(int green, int yellow, int red) {
        greenTime = green;
        yellowTime = yellow;
        redTime = red;
        cout << "[" << roadName << "] All timings updated: G=" << green
            << "s Y=" << yellow << "s R=" << red << "s\n";
    }

    // ───────────────────────────────────────────
    // UTILITY MEMBER FUNCTIONS
    // ───────────────────────────────────────────

    void setState(string state) {
        if (state == "GREEN" || state == "YELLOW" || state == "RED")
            currentState = state;
        else
            cout << "Invalid state! Use GREEN, YELLOW, or RED.\n";
    }

    void addVehicles(int n) { vehicleCount += n; }
    void removeVehicles(int n) { vehicleCount = (vehicleCount >= n) ? vehicleCount - n : 0; }

    int getTotalCycleTime() const { return greenTime + yellowTime + redTime; }
    string getRoadName()    const { return roadName; }
    int getGreenTime()      const { return greenTime; }
    int getRedTime()        const { return redTime; }
    int getYellowTime()     const { return yellowTime; }
    int getVehicleCount()   const { return vehicleCount; }
    string getState()       const { return currentState; }

    // Throughput: vehicles that can pass per full cycle (approx.)
    double throughput() const {
        if (getTotalCycleTime() == 0) return 0;
        return (double)vehicleCount * greenTime / getTotalCycleTime();
    }

    // Efficiency ratio (0.0 to 1.0)
    double efficiency() const {
        if (getTotalCycleTime() == 0) return 0;
        return (double)greenTime / getTotalCycleTime();
    }

    // ───────────────────────────────────────────
    // OPERATOR OVERLOADING
    // ───────────────────────────────────────────

    // 1. + operator: Merge two signals (combine vehicle counts, avg timings)
    TrafficSignal operator+(const TrafficSignal& other) const {
        TrafficSignal merged;
        merged.roadName = roadName + " & " + other.roadName;
        merged.greenTime = (greenTime + other.greenTime) / 2;
        merged.yellowTime = (yellowTime + other.yellowTime) / 2;
        merged.redTime = (redTime + other.redTime) / 2;
        merged.vehicleCount = vehicleCount + other.vehicleCount;
        merged.currentState = "RED";
        return merged;
    }

    // 2. - operator: Remove n vehicles from signal
    TrafficSignal operator-(int n) const {
        TrafficSignal result(*this);
        result.vehicleCount = (vehicleCount >= n) ? vehicleCount - n : 0;
        return result;
    }

    // 3. * operator: Scale green/red timings by a factor (traffic surge)
    TrafficSignal operator*(double factor) const {
        TrafficSignal result(*this);
        result.greenTime = (int)(greenTime * factor);
        result.redTime = (int)(redTime * factor);
        return result;
    }

    // 4. == operator: Two signals are equal if they have same timings
    bool operator==(const TrafficSignal& other) const {
        return (greenTime == other.greenTime &&
            yellowTime == other.yellowTime &&
            redTime == other.redTime);
    }

    // 5. < operator: Compare by vehicle count (congestion level)
    bool operator<(const TrafficSignal& other) const {
        return vehicleCount < other.vehicleCount;
    }

    // 6. > operator: Compare by vehicle count
    bool operator>(const TrafficSignal& other) const {
        return vehicleCount > other.vehicleCount;
    }

    // 7. << operator: Output display (friend function)
    friend ostream& operator<<(ostream& out, const TrafficSignal& ts) {
        out << "╔══════════════════════════════════════╗\n";
        out << "  Road       : " << ts.roadName << "\n";
        out << "  State      : " << ts.currentState << "\n";
        out << "  Green      : " << ts.greenTime << "s\n";
        out << "  Yellow     : " << ts.yellowTime << "s\n";
        out << "  Red        : " << ts.redTime << "s\n";
        out << "  Cycle Time : " << ts.getTotalCycleTime() << "s\n";
        out << "  Vehicles   : " << ts.vehicleCount << "\n";
        out << "  Throughput : " << ts.throughput() << " vehicles/cycle\n";
        out << "  Efficiency : " << ts.efficiency() * 100 << "%\n";
        out << "╚══════════════════════════════════════╝\n";
        return out;
    }
};

#endif#pragma once
