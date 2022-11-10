#include <iostream>
#include "technician.h"
#include "computer.h"
#include "electronics.h"

const int MAX_NUM_TECHNICIAN = 10;

// TODO: initialize the static varibles of class Technician
Technician* Technician::technician_list[MAX_NUM_TECHNICIAN] = {nullptr};
int Technician::num_technician = 0;

// TODO: Implement the constructor
Technician::Technician(std::string name, Diagnosis_Tool* diagnosis_tool){
    this->name = name;
    this->diagnosis_tool = diagnosis_tool;
    technician_list[num_technician] = this;
    num_technician++;
    num_order_finished = 0;
}

Technician::~Technician(){
    delete diagnosis_tool;
}

CPU* Technician::acquire_CPU(CPU_Model model) const {
    return new CPU(model);
}

MEM* Technician::acquire_MEM(MEM_Model model) const {
    return new MEM(model);
}

// TODO: implement repair function
void Technician::repair(Computer* computer){
    
    /*
    bool Diagnosis_Tool::diagnose(Electronics* electronics);
    CPU_Model Diagnosis_Tool::get_CPU_Model(CPU* cpu);
    MEM_Model Diagnosis_Tool::get_MEM_Model(MEM* mem);
    CPU* Technician::acquire_CPU(CPU_Model model) const; 
    MEM* Technician::acquire_MEM(MEM_Model model) const;*/ 
    if (this->diagnosis_tool->diagnose(computer->cpu) == false){
        CPU_Model CPU_MODELS = this->diagnosis_tool->get_CPU_Model(computer->cpu);
        delete computer->cpu;
        computer->cpu = this->acquire_CPU(CPU_MODELS);
        //this->num_order_finished++;
        CPU::defect_count++;
    }

    if (this->diagnosis_tool->diagnose(computer->mem) == false){
        MEM_Model MEM_MODELS = this->diagnosis_tool->get_MEM_Model(computer->mem);
        delete computer->mem;
        computer->mem = this->acquire_MEM(MEM_MODELS);
        //this->num_order_finished++;
        MEM::defect_count++;
    }

    this->num_order_finished++;
    
    
}

void Technician::print_report(){
    std::cout << "----------------------" << std::endl;
    std::cout << "REPORT FOR TECHNICIANS" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout.width(20);
    std::cout << std::left << "NAME" << "ORDERS_COMPLETED" << std::endl;
    for(int i = 0; i < num_technician; ++i){
        std::cout.width(20);
        std::cout << std::left << technician_list[i]->name << technician_list[i]->num_order_finished << std::endl;
    }
}
