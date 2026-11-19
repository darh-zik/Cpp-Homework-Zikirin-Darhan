#include <exception>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <functional>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <map>


//преобъявление функций
std::string GetnWord(std::string request, int n);
int GetNumber(std::string request, int n);
bool IsNumber(std::string word);
double GetDouble(std::string request, int n);


//абстрактный базовый класс
class InventoryItem {
 protected:
  std::string id_;
  std::string name_;
 public:
  
  InventoryItem(std::string id, std::string name) : id_(id), name_(name) {}
  // std::string InvetoryId() { return id_; }
  virtual std::string inventoryId() const = 0;
  virtual std::string name() const = 0;
  virtual std::string describe() const = 0;
  virtual ~InventoryItem() = default;
  bool operator<(const InventoryItem& Item2) const { return id_ < Item2.id_;}
};

//структура ошибок (делаем первым чтобы мочь вызывать ошибки при создании классов сразу)
class AnyError : public std::exception {

};
class InspectionError : public AnyError {

};
class SyntaxError : public AnyError {

};
class GettingNumberError : public SyntaxError {

};
class NumberTypeError : public SyntaxError {

};
class DuplicateIdError : public SyntaxError {

};
class SimplicityValueError : public SyntaxError {

};

//техосмотр реализуем для любых объектов негоже хранить сломанные шлема и докстанции
std::shared_ptr<InventoryItem> Inspection(std::unique_ptr<InventoryItem> Item) {
  std::string broken = "broken";
  std::string BROKEN = "BROKEN";
  const int c_broken_lenght = 6;
  std::string name = Item->name();
  int n = name.size();
  bool isBroken = false;
  for (int i = 0; i + c_broken_lenght <= n; ++i) {
    if (name[i] == broken[0] || name[i] == BROKEN[0]) {
      bool isBrokenSubstr = true;
      for (int j = i; j < n && j < i + c_broken_lenght; ++j) {
        if (name[j] != broken[j - i] && name[j] != BROKEN[j - i]) {
          isBrokenSubstr = false;
          break;
        }
      }
      if (isBrokenSubstr) {
        isBroken = true;
        break;
      }
    }
  }
  if (isBroken) {
    throw InspectionError();
  }
  return std::shared_ptr<InventoryItem>(Item.release());
}

//прямые наследники базового класса

class Transport : public InventoryItem {
 private:
  int simplicity_;
  int wheels_;
 public:
Transport(std::string id, std::string name, int simplicity, int wheels)
            : InventoryItem(id, name), simplicity_(simplicity), wheels_(wheels) {
              if (simplicity < 1 || simplicity > 10) {
                throw SimplicityValueError();
              }
            }
  std::string inventoryId() const override {
    return id_;
  }
  std::string name() const override {
    return name_;
  }
  int simplicity() const {
    return simplicity_;
  }
  std::string describe() const override {
    return id_ + " " + name_;
  }
  int wheels() const {
    return wheels_;
  }
};


class Thing : public InventoryItem {
 private:

 public:
  Thing(std::string id, std::string name): InventoryItem(id, name) {}
  std::string inventoryId() const override {
    return id_;
  }
  std::string name() const override {
    return name_;
  }
  std::string describe() const override {
    return id_ + " " + name_;
  }
};


//класс потребителя энергии
class EnergyConsumer {
 protected:
  double dailyenergy_;

 public:
  EnergyConsumer(double dailyenergy) : dailyenergy_(dailyenergy) {}
  virtual double dailyenergy() const = 0;
  virtual ~EnergyConsumer() = default;
};

//различные классы транспортов
//самокат (не электрический)
class Scooter : public Transport {
 public:
  Scooter(std::string id, std::string name, int simplicity)
                      : Transport(id, name, simplicity, 2) {}
};

//электросамокат
class eScooter : public Transport, public EnergyConsumer {
 public:
  eScooter(std::string id, std::string name, int simplicity, double energy)
                      : Transport(id, name, simplicity, 2), EnergyConsumer(energy) {}
  double dailyenergy() const override {
    return dailyenergy_;
  }
};

//велосипед я решил для него ввести еще колеса потому что велосипеды бывают не только двух колесные а самокат считаем всегда двух колесным
class Bike : public Transport {
 public:
  Bike(std::string id, std::string name, int simplicity, int wheels)
                        : Transport(id, name, simplicity, wheels) {}
};
//электровелосипед
class eBike : public Transport, public EnergyConsumer {
 public:
  eBike(std::string id, std::string name, int simplicity, int wheels, double energy)
                      : Transport(id, name, simplicity, wheels), EnergyConsumer(energy) {}
  double dailyenergy() const override {
    return dailyenergy_;
  }
};

//класс объектов для защиты тела
class Protecting {
 public:
  int durability_;
  Protecting(int durability) : durability_(durability) {};
};

//классы различных вещей для защиты
class Helmet : public Thing, public Protecting  {
 public:
  Helmet(std::string id, std::string name, int durability)
                      : Thing(id, name), Protecting(durability) {}
};
class Knee_pads : public Thing, public Protecting  {
 public:
  Knee_pads(std::string id, std::string name, int durability)
                      : Thing(id, name), Protecting(durability) {}
};
class Elbow_pads : public Thing, public Protecting {
 public:
  Elbow_pads(std::string id, std::string name, int durability)
                      : Thing(id, name), Protecting(durability) {}
};

//другие вещи
class Dock : public Thing, public EnergyConsumer {
 public:
  Dock(std::string id, std::string name, double energy)
                      : Thing(id, name), EnergyConsumer(energy) {}
  double dailyenergy() const override {
    return dailyenergy_;
  }
};

//раз ввели колеса то можно ввести и запасные колеса, а их мне кажется удобнее хранить не по одному поэтому сделаем для них еще колличество в пачке
class Spare_wheel : public Thing {
 private:
  int count_;
 public:
  Spare_wheel(std::string id, std::string name, int count)
                      : Thing(id, name), count_(count) {}
  int count() const { return count_; }
};

//Ну и раз есть потребители энергии то нужны и батарейки
class battery : public Thing {
 private:
  double capacity_;
 public:
  battery(std::string id, std::string name, double capacity)
      : Thing(id, name), capacity_(capacity) {}
};

//шаблончики, тут треш конечно наваян сначала функция которая принимает много аргументов функции которые извлекают либо double или int 
//соответсвие лежит в getcreator он принимает слово типа и возвращает набор лямбда функций которые используются в createitem
template <typename T, typename... Functions>
std::unique_ptr<InventoryItem> CreateItem(
    std::string request, Functions... funcs) {

  return std::make_unique<T>(
      GetnWord(request, 2),
      GetnWord(request, 3),
      funcs(request)...);
}
const std::function<std::unique_ptr<InventoryItem>(std::string)>&
GetCreator(const std::string& type) {

static const std::unordered_map<std::string,
    std::function<std::unique_ptr<InventoryItem>(std::string)>> creations = {

  {"scooter", [](std::string request) {
    return CreateItem<Scooter>(request,
        [](const std::string& r) { return GetNumber(r, 4); });
  }},

  {"escooter", [](std::string request) {
    return CreateItem<eScooter>(request,
        [](const std::string& r) { return GetNumber(r, 4); },
        [](const std::string& r) { return GetDouble(r, 5); });
  }},

  {"bike", [](std::string request) {
    return CreateItem<Bike>(request,
        [](const std::string& r) { return GetNumber(r, 4); },
        [](const std::string& r) { return GetNumber(r, 5); });
  }},

  {"ebike", [](std::string request) {
    return CreateItem<eBike>(request,
        [](const std::string& r) { return GetNumber(r, 4); },
        [](const std::string& r) { return GetNumber(r, 5); },
        [](const std::string& r) { return GetDouble(r, 6); });
  }},

  {"helmet", [](std::string request) {
    return CreateItem<Helmet>(request,
        [](const std::string& r) { return GetNumber(r, 4); });
  }},

  {"knee_pads", [](std::string request) {
    return CreateItem<Knee_pads>(request,
        [](const std::string& r) { return GetNumber(r, 4); });
  }},

  {"elbow_pads", [](std::string request) {
    return CreateItem<Elbow_pads>(request,
        [](const std::string& r) { return GetNumber(r, 4); });
  }},

  {"dock", [](std::string request) {
    return CreateItem<Dock>(request,
        [](const std::string& r) { return GetDouble(r, 4); });
  }},

  {"spare_wheel", [](std::string request) {
    return CreateItem<Spare_wheel>(request,
        [](const std::string& r) { return GetNumber(r, 4); });
  }},

  {"battery", [](std::string request) {
    return CreateItem<battery>(request,
        [](const std::string& r) { return GetDouble(r, 4); });
  }}

  };

  auto it = creations.find(type);

  if (it == creations.end()) {
    throw SyntaxError();
  }

  return it->second;
}


//функция которые соединяет все это и которую мы будет вызывать для создания
std::shared_ptr<InventoryItem> CreateInventoryItem(std::string request) {
  std::string type = GetnWord(request, 1);
  return Inspection(GetCreator(type)(request));
}

//функция взятия n-го по счёту в строке слова
std::string GetnWord(std::string request, int n) {
  int start = 0;
  int j = 1;
  auto end = request.find(' ', 0);
  size_t len = request.size();
  while (start < len && j < n) {
    if (end == std::string::npos) {
      return "";
    }
    start = end + 1;
    end = request.find(' ', start);
    ++j;
  }
  return request.substr(start, end - start);
}

//проверка на число
bool IsNumber(std::string word) {
  int i = 0;
  size_t n = word.size();
  bool ans = (n > 0);
  for (int i = 0; i < n; ++i) {
    //такое тупо быстрее писалось чем гуглить их коды в ASCII и все такое
    if (word[i] != '1' && word[i] != '2' && word[i] != '3' && word[i] != '4' && word[i] != '5' && word[i] != '6' && word[i] != '7' && word[i] != '8' && word[i] != '9' && word[i] != '0') {
      ans = false;
      break;
    }
  }
  return ans;
}
int GetNumber(std::string request, int n) {
  int start = 0;
  int j = 1;
  auto end = request.find(' ', 0);
  size_t len = request.size();
  if (n < 1) {
    throw GettingNumberError();
  }
  while (start < len && j < n) {
    if (end == std::string::npos) {
      throw GettingNumberError();
    }
    start = end + 1;
    end = request.find(' ', start);
    ++j;
  }
  if (end == std::string::npos) {
    end = len;
  }
  if (IsNumber(request.substr(start, end - start))) {
    int ans = 0;
    for (int i = start; i < end; ++i) {
      int t = (request[i] - '0');
      ans *= 10;
      ans += t;
    }
    return ans;
  }
  throw GettingNumberError();
}
double GetDouble(std::string request, int n) {
  std::string word = GetnWord(request, n);
  size_t end = 0;
  double ans;
  try {
    ans = std::stod(word, &end);
  }
  catch (const std::exception&) {
    throw GettingNumberError();
  }
  if (end != word.size()) {
    throw GettingNumberError();
  }
  if (ans < 0) {
    throw NumberTypeError();
  }
  return ans;
}
int main () {
  std::string request = "";
  std::map <std::string, std::shared_ptr<InventoryItem> > park;
  while (request != "quit") {
    try {
      if (request.starts_with("help")) {
        std::cout << "list of commands and their syntax\n";
        std::cout << "add \n";
      } 
      else if (request.starts_with("add ")) {
        request = request.substr(4);
        std::string id = GetnWord(request, 2);
        if (id.empty()) {
          throw SyntaxError();
        }
        if (park.find(id) != park.end()) {
          throw DuplicateIdError();
        }
        park[id] = CreateInventoryItem(request);
      }
      else if (request == "energy") {
        double energy = 0;
        for (const std::pair<const std::string, std::shared_ptr<InventoryItem>>& item : park) {
          std::shared_ptr<EnergyConsumer> consumer =
                std::dynamic_pointer_cast<EnergyConsumer>(item.second);
          if (consumer != nullptr) {
            energy += consumer->dailyenergy();
          }
        }
        std::cout << std::fixed << std::setprecision(1) << energy << '\n';
      }
      else if (request == "list") {
        for (const std::pair<const std::string, std::shared_ptr<InventoryItem>>& item : park) {
          std::cout << item.first << '\n';
        }
      }
      else if (request.starts_with(" ")) {
      }
      else if (request.starts_with(" ")) {
      }
      else {
        std::cout << "Please enter the correct command or just enter help.\n";
      }
    }
    catch (const InspectionError&) {
      std::cout << "Object is broken\n";
    }
    catch (const DuplicateIdError&) {
      std::cout << "ID already exists\n";
    }
    catch (const GettingNumberError&) {
      std::cout << "Invalid number\n";
    }
    catch (const NumberTypeError&) {
      std::cout << "Number cannot be negative\n";
    }
    catch (const SimplicityValueError&) {
      std::cout << "Simplicity must be between 1 and 10\n";
    }
    catch (const SyntaxError&) {
      std::cout << "Please enter the correct command or just enter help.\n";
    }
    std::getline(std::cin, request);
  }
  return 0;
}