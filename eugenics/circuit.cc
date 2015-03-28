#include "circuit.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <string>

#include "utility.h"

using namespace std;

Circuit::Circuit(vector<bool> inputs, int o)
    : output_no(o), input_no(inputs.size()) {
  for (bool input : inputs) {
    Gate* wire = new Wire(input);
    gates.push_back(wire);
  }
}
Circuit::Circuit(int inputs, int o) : output_no(o), input_no(inputs) {
  for (int i = 0; i < input_no; ++i) {
    Gate* wire = new Wire(false);
    gates.push_back(wire);
  }
}

int Circuit::addGate(GateType gate_type, int index_1) {
  Gate* built_gate = nullptr;
  Gate* input_1 = gates[index_1];
  if (gate_type == NOT) {
    built_gate = new Not(input_1);
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) + " NOT " +
                         std::to_string(index_1);
    errlog(errmsg);
  } else if (gate_type == WIRE) {
    built_gate = new Wire(input_1);
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) + " WIRE " +
                         std::to_string(index_1);
    errlog(errmsg);
  }
  assert(built_gate != nullptr);
  gates.push_back(built_gate);
  return gates.size();
}

int Circuit::addGate(GateType gate_type, int index_1, int index_2) {
  Gate* built_gate = nullptr;
  Gate* input_1 = gates[index_1];
  Gate* input_2 = gates[index_2];
  if (gate_type == AND) {
    built_gate = new And(input_1, input_2);
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) + " AND " +
                         std::to_string(index_1) + " " + std::to_string(index_2);
    errlog(errmsg);
  } else if (gate_type == OR) {
    built_gate = new Or(input_1, input_2);
    std::string errmsg = "Circuit::addGate: " + std::to_string(gates.size()) + " OR " +
                         std::to_string(index_1) + " " + std::to_string(index_2);
    errlog(errmsg);
  }
  assert(built_gate != nullptr);
  gates.push_back(built_gate);
  return gates.size();
}

vector<vector<bool>> Circuit::evaluateAllInputs() {
  vector<vector<bool>> inputs = getPossibleInputs();
  vector<vector<bool>> outputs;
  for (vector<bool> input : inputs) {
    outputs.push_back(evaluateInputSet(input));
  }
  assert(!outputs.empty());
  return outputs;
}

vector<bool> Circuit::evaluateInputSet(vector<bool> input_set) {
  vector<bool> result;
  for (int i = 0; i < input_no; ++i) {
    (dynamic_cast<Wire*>(gates[i]))->setInput(input_set[i]);
    std::string errmsg = "Circuit::evaluateInputSet: input_set[" +
                         std::to_string(i) + "] = " + std::to_string(input_set[i]);
    errlog(errmsg);
  }
  reverse_iterator<vector<Gate*>::iterator> r = gates.rbegin();
  for (int i = 0; i < output_no; ++i) {
    bool output = r[i]->evaluate();

    std::string errmsg = "Circuit::evaluateInputSet: output[" +
                         std::to_string(i) + "] = " + std::to_string(output);
    errlog(errmsg);

    result.insert(result.begin(), output);
  }
  return result;
}

vector<vector<bool>> Circuit::getPossibleInputs() {
  vector<vector<bool>> possibilities;
  for (int i = 0; i < pow(2, input_no); ++i) {
    cout << "Input set: " << i << ":";
    vector<bool> row;
    for (int j = input_no - 1; j >= 0; --j) {
      int current_bit = (i >> j) & 1;
      row.push_back(current_bit);
    }
    assert(row.size() == (unsigned int)input_no);
    possibilities.push_back(row);
  }
  return possibilities;
}