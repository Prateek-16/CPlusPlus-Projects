#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

class Vehicle {
    public:
        string vehicleType;
        string regNo;
        string color;
        Vehicle(string vehicleType , string regNo , string color) 
            : vehicleType(vehicleType) , regNo(regNo) , color(color) {}
};

class Slot{
    public:
        int slotNo;
        string slotType;
        bool isOccupied;
        Vehicle* parkedVehicle;

        Slot(int slotNo, string slotType) : slotNo(slotNo) , slotType(slotType) {}

        void assignVehicle(Vehicle* vehicle) {
            isOccupied = true;
            parkedVehicle = vehicle;
        }

        void removeVehicle() {
            isOccupied = false;
            parkedVehicle = nullptr;
        }

};

class Floor{ 
    public:
    int FloorNo;
    vector<Slot> slots;
        Floor(int FloorNo,int noOfSlots) : FloorNo(FloorNo){
            //1st Slot is reserved for Truck as its size is large
            //2nd and 3rd Slot is reserved for Bike as its size is small
            //Rest Slots are reserved for cars
            for(int i = 1 ; i <= noOfSlots ; i++){
                if(i == 1){
                    slots.push_back(Slot(i,"TRUCK"));
                }
                else if(i == 2 || i == 3){
                    slots.push_back(Slot(i,"BIKE"));
                }
                else{
                    slots.push_back(Slot(i,"CAR"));
                }
            }
        }

        Slot* FindFreeSlot(string vehileType){
            for(int i = 0 ; i < slots.size();i++){
                if(slots[i].isOccupied == false && slots[i].slotType == vehileType){
                    return &slots[i];
                }
            }
            return nullptr;
        }

        int countFreeSlots(string vehicleType) {
            int count = 0;
            for (auto& slot : slots) {
                if (!slot.isOccupied && slot.slotType == vehicleType) {
                    count++;
                }
            }
            return count;
        }

        vector<int> getFreeSlots(string vehicleType) {
            vector<int>freeSlots;
            for(auto& slot : slots){
                if(slot.isOccupied == false && slot.slotType == vehicleType)
                freeSlots.push_back(slot.slotNo);
            }
            return freeSlots;
        }

        vector<int> getOccupiedSlots(string vehicleType) {
            vector<int>occupiedSlots;
            for(auto& slot : slots){
                if(slot.isOccupied == true && slot.slotType == vehicleType)
                occupiedSlots.push_back(slot.slotNo);
            }
            return occupiedSlots;
        }
};

class Ticket {
public:
    string ticketId;
    Vehicle* vehicle;
    Slot* slot;

    Ticket(){}
    Ticket(string parkingLotId, int floorNo, int slotNo, Vehicle* vehicle, Slot* slot) 
        : vehicle(vehicle), slot(slot) {
        stringstream ss;
        ss << parkingLotId << "_" << floorNo << "_" << slotNo;
        this->ticketId = ss.str();
    }
};

class ParkingLot{
    public:
    string parkingLotId;
    vector<Floor> floors;
    unordered_map<string, Ticket> tickets;

        ParkingLot(string parkingLotId, int noOfFloors, int noOfSlotsPerFloor) : parkingLotId(parkingLotId)  {
            //Now i need to Create the Floors
            for(int i = 1; i <= noOfFloors; i++){
                floors.push_back(Floor(i, noOfSlotsPerFloor));
            }
        }

        Ticket* parkVehicle(Vehicle* vehicle) {
            for(int i = 0;i<floors.size();i++){
                Slot* slot = floors[i].FindFreeSlot(vehicle->vehicleType);
                if(slot != nullptr){
                    slot->assignVehicle(vehicle);
                    Ticket ticket(parkingLotId, floors[i].FloorNo, slot->slotNo, vehicle, slot);
                    tickets[ticket.ticketId] = ticket;
                    return &tickets[ticket.ticketId];
                }
            }
            return nullptr;
        }

        void unparkVehicle(string ticketId){
            if(tickets.find(ticketId) != tickets.end()){
                tickets[ticketId].slot->removeVehicle();
                tickets.erase(ticketId);
                cout << "Vehicle with ticket ID " << ticketId << " has been unparked." << endl;
            } else {
            cout << "Invalid ticket ID." << endl;
            }
        }

        void displayFreeCount(string vehicleType) {
            for (auto& floor : floors) {
                int count = floor.countFreeSlots(vehicleType);
                cout << "Floor " << floor.FloorNo << ": " << count << " free slots for " << vehicleType << endl;
            }
        }

        void displayFreeSlots(string vehicleType) {
            for (auto& floor : floors) {
                vector<int> freeSlots = floor.getFreeSlots(vehicleType);
                cout << "Floor " << floor.FloorNo << ": ";
                for (int slotNo : freeSlots) {
                    cout << slotNo << " ";
                }
                cout << endl;
            }
        }

        void displayOccupiedSlots(string vehicleType) {
            for (auto& floor : floors) {
                vector<int> occupiedSlots = floor.getOccupiedSlots(vehicleType);
                cout << "Floor " << floor.FloorNo << ": ";
                for (int slotNo : occupiedSlots) {
                    cout << slotNo << " ";
                }
                cout << endl;
            }
        }
};

int main(){
    ParkingLot* parkingLot;
    string command;
    while(getline(cin,command)){
        istringstream iss(command);
        vector<string>tokens;
        string token;
        while(iss >> token){
            tokens.push_back(token);
        }
        if(tokens[0] == "create_parking_lot"){
            string parkingLotId = tokens[1];
            int noOfFloors = stoi(tokens[2]);
            int noOfSlotsPerFloor = stoi(tokens[3]);
            parkingLot = new ParkingLot(parkingLotId, noOfFloors, noOfSlotsPerFloor);
            cout << "Created parking lot with " << noOfFloors << " floors and " << noOfSlotsPerFloor << " slots per floor." << endl;
        }
        else if(tokens[0] == "park_vehicle"){
            string vehicleType = tokens[1];
            string regNo = tokens[2];
            string color = tokens[3];
            Vehicle* vehicle = new Vehicle(vehicleType,regNo,color);
            Ticket* ticket = parkingLot->parkVehicle(vehicle);
            if (ticket != nullptr) {
                cout << "Parked vehicle. Ticket ID: " << ticket->ticketId << endl;
            }
        }
        else if(tokens[0] == "unpark_vehicle"){
            string ticketId = tokens[1];
            parkingLot->unparkVehicle(ticketId);
        }
        else if (tokens[0] == "display"){
            if(tokens[1] == "free_count"){
                parkingLot->displayFreeCount(tokens[2]);
            }
            else if(tokens[1] == "free_slots"){
                parkingLot->displayFreeSlots(tokens[2]);
            }
            else if(tokens[1] == "occupied_slots"){
                parkingLot->displayOccupiedSlots(tokens[2]);
            }
        }
        else if (tokens[0] == "exit") {
            break;
        }
    }
    return 0;
}