#include <iostream>

using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;
    double rentalPrice;

public:
    Vehicle(const string& make, const string& model, int year, double rentalPrice)
        : make(make), model(model), year(year), rentalPrice(rentalPrice) {}

    virtual void displayDetails() = 0;
    virtual double calculateRentalCost(int numDays) = 0;
};

class Car : public Vehicle {
public:
    Car(const string& make, const string& model, int year, double rentalPrice)
        : Vehicle(make, model, year, rentalPrice) {}

    void displayDetails() override {
        cout << "Car Details:\n";
        cout << "Make: " << make << "\n";
        cout << "Model: " << model << "\n";
        cout << "Year: " << year << "\n";
        cout << "Rental Price: $" << rentalPrice << " per day\n";
    }

    double calculateRentalCost(int numDays) override {
        return rentalPrice * numDays;
    }
};

class Truck : public Vehicle {
private:
    double cargoCapacity;

public:
    Truck(const string& make, const string& model, int year, double rentalPrice, double cargoCapacity)
        : Vehicle(make, model, year, rentalPrice), cargoCapacity(cargoCapacity) {}

    void displayDetails() override {
        cout << "Truck Details:\n";
        cout << "Make: " << make << "\n";
        cout << "Model: " << model << "\n";
        cout << "Year: " << year << "\n";
        cout << "Rental Price: $" << rentalPrice << " per day\n";
        cout << "Cargo Capacity: " << cargoCapacity << " tons\n";
    }

    double calculateRentalCost(int numDays) override {
        return rentalPrice * numDays;
    }
};

class Admin {
public:
    void addCarDetails(Vehicle** vehicles, int& numVehicles, int maxVehicles) {
        if (numVehicles >= maxVehicles) {
            cout << "Maximum number of vehicles reached.\n";
            return;
        }

        string make, model;
        int year;
        double rentalPrice;

        cout << "Enter car make: ";
        cin >> make;
        cout << "Enter car model: ";
        cin >> model;
        cout << "Enter car year: ";
        cin >> year;
        cout << "Enter car rental price per day: ";
        cin >> rentalPrice;

        vehicles[numVehicles] = new Car(make, model, year, rentalPrice);
        numVehicles++;
        cout << "Car details added successfully.\n";
    }

    void addTruckDetails(Vehicle** vehicles, int& numVehicles, int maxVehicles) {
        if (numVehicles >= maxVehicles) {
            cout << "Maximum number of vehicles reached.\n";
            return;
        }

        string make, model;
        int year;
        double rentalPrice, cargoCapacity;

        cout << "Enter truck make: ";
        cin >> make;
        cout << "Enter truck model: ";
        cin >> model;
        cout << "Enter truck year: ";
        cin >> year;
        cout << "Enter truck rental price per day: ";
        cin >> rentalPrice;
        cout << "Enter the cargo capacity in tons: ";
        cin >> cargoCapacity;

        vehicles[numVehicles] = new Truck(make, model, year, rentalPrice, cargoCapacity);
        numVehicles++;
        cout << "Truck details added successfully.\n";
    }
};

class User {
public:
    void viewVehicleDetails(Vehicle** vehicles, int numVehicles) {
        cout << "Vehicle Details:\n";
        for (int i = 0; i < numVehicles; i++) {
            vehicles[i]->displayDetails();
            cout << "-------------------\n";
        }
    }

    void rentVehicle(Vehicle** vehicles, int numVehicles) {
        int choice;
        cout << "Enter the index of the vehicle you want to rent: ";
        cin >> choice;

        if (choice >= 0 && choice < numVehicles) {
            int numDays;
            cout << "Enter the number of days you want to rent the vehicle: ";
            cin >> numDays;

            double totalCost = vehicles[choice]->calculateRentalCost(numDays);
            cout << "Rent Successful!\n";
            cout << "Total Cost: $" << totalCost << "\n";
        } else {
            cout << "Invalid vehicle choice.\n";
        }
    }
};

int main() {
    const int MAX_VEHICLES = 10;
    Vehicle* vehicles[MAX_VEHICLES];
    int numVehicles = 0;

    Admin admin;
    User user;

    char choice;

    do {
        cout << "Choose an option:\n";
        cout << "1. Add car details (Admin)\n";
        cout << "2. Add truck details (Admin)\n";
        cout << "3. View vehicle details (User)\n";
        cout << "4. Rent a vehicle (User)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                admin.addCarDetails(vehicles, numVehicles, MAX_VEHICLES);
                break;
            case '2':
                admin.addTruckDetails(vehicles, numVehicles, MAX_VEHICLES);
                break;
            case '3':
                user.viewVehicleDetails(vehicles, numVehicles);
                break;
            case '4':
                user.rentVehicle(vehicles, numVehicles);
                break;
            case '5':
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != '5');

    for (int i = 0; i < numVehicles; i++) {
        delete vehicles[i];
    }

    return 0;
}

