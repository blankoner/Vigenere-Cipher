#include "include/cipher.h"

unsigned int Cipher::indexMoverForEncryption(int index)
{
  int newMoveNum = moveNum_;
  if((index+moveNum_) > (alphabet_.size()-1))
  {
    newMoveNum -= ((alphabet_.size()-1)-index);
    return (newMoveNum-1);
  }
  return (index+moveNum_);
}

unsigned int Cipher::indexMoverForDecryption(int index)
{
  if((index-moveNum_) < 0)
  {
    return alphabet_.size()-(moveNum_-index);
  }
  return (index-moveNum_);
}

void Cipher::showVector(const std::vector<char>& vector)
{
  for(int i=0;i<vector.size();i++)
  {
    std::cout << vector[i];
  }
  std::cout << std::endl;
}

void Cipher::smallToBig(char& letter)
{
  if(((int)letter >= 97) && ((int)letter <= 122))
  {
    letter = (char)((int)letter-32);
  }
}

void Cipher::readMessage()
{
  std::fstream file;
  std::string filePath;

  std::cout << "Enter the message-file path:" << std::endl;
  std::cin >> filePath;

  file.open(filePath, std::ios::in);
  if(file.good())
  {
    std::string line;
    while(std::getline(file, line))
    {
      for(int i=0;i<line.size();i++)
      {
        smallToBig(line[i]);
        message_.push_back(line[i]);
      }
      if(!file.eof())
      {
        message_.push_back('\n');
      }
    }
    file.close();
  }
  else
  {
    std::cerr << "Message-file's path error!";
  }
}

void Cipher::readPassword()
{
  std::string sign;
  std::cout << "Type a password:" << std::endl;
  std::getline(std::cin >> std::ws, sign);
  for(int i=0;i<sign.size();i++)
  {
    smallToBig(sign[i]);
    password_.push_back(sign[i]);
  }
}

void Cipher::saveResult()
{
  std::fstream file;
  std::string filePath;

  std::cout << "Enter the result-file path: " << std::endl;
  std::cin >> filePath;

  file.open(filePath, std::ios::out);
  if(file.good())
  {
    for(int i=0;i<result_.size();i++)
    {
      file << result_[i];
    }
    file.close();
  }
  else
  {
    std::cerr << "Result-file opening error!";
  }
}

int Cipher::alphabetCheck(const char& sign)
{
  for(int i=0;i<alphabet_.size();i++)
  {
    if(alphabet_[i] == sign)
    {
      return i;
    }
  }
  return -1;
}

void Cipher::buildEncryptionResult()
{
  int passwordInx = 0;
  for(int i=0;i<message_.size();i++)
  {
    int index = alphabetCheck(message_[i]);
    if(index != -1)
    {
      if(passwordInx>(password_.size()-1))
      {
        moveNum_ = moveIndex(password_[passwordInx%password_.size()]);
      }
      else
      {
        moveNum_ = moveIndex(password_[passwordInx]);
      }

      result_.push_back(alphabet_[indexMoverForEncryption(index)]);
      passwordInx++;
    }
    else
    {
      result_.push_back(message_[i]);
    }
  }
}

void Cipher::buildDecryptionResult()
{
  int passwordInx = 0;
  for(int i=0;i<message_.size();i++)
  {
    int index = alphabetCheck(message_[i]);
    if(index != -1)
    {
      if(passwordInx>(password_.size()-1))
      {
        moveNum_ = moveIndex(password_[passwordInx%password_.size()]);
      }
      else
      {
        moveNum_ = moveIndex(password_[passwordInx]);
      }

      result_.push_back(alphabet_[indexMoverForDecryption(index)]);
      passwordInx++;
    }
    else
    {
      result_.push_back(message_[i]);
    }
  }
}

void Cipher::start()
{
  int option = 0;
  std::cout << "Choose the option: " << std::endl;
  std::cout << "1. Encryption." << std::endl;
  std::cout << "2. Decryption." << std::endl;
  std::cin >> option;

  switch(option)
  {
  case 1:
    readPassword();
    readMessage();
    buildEncryptionResult();
    break;
  case 2:
    readPassword();
    readMessage();
    buildDecryptionResult();
    break;
  default:
    std::cerr << "Invalid option!";
  }
  saveResult();
}

unsigned int Cipher::moveIndex(const char& sign)
{
  for(int i=0;i<alphabet_.size();i++)
  {
    if(alphabet_[i] == sign)
    {
      return i;
    }
  }
  return 0;
}