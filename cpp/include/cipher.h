#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Cipher
{
private:
  std::vector<char> alphabet_ = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
                                'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                                'V', 'W', 'X', 'Y', 'Z', '0', '1', 
                                '2', '3', '4', '5', '6', '7', '8', 
                                '9'};
  int moveNum_;
  std::vector<char> message_;
  std::vector<char> password_;
  std::vector<char> result_;

public:
  Cipher():moveNum_(0){}
  ~Cipher(){}
  
  unsigned int indexMoverForEncryption(int index);
  unsigned int indexMoverForDecryption(int index);
  void showVector(const std::vector<char>& vector);
  void smallToBig(char& letter);
  void readMessage();
  void readPassword();
  void saveResult();
  unsigned int moveIndex(const char& sign);
  int alphabetCheck(const char& sign);
  void buildEncryptionResult();
  void buildDecryptionResult();
  void start();
};