#include <array>
#include <iostream>
#include <string>
#include <string_view>

class Layer {
public:
  Layer(const std::string_view &name, const std::string_view &header)
      : name(name), header(header) {}

  std::string Transfer(const std::string &message) const {
    return header + " " + message;
  }

  std::string Receive(std::string &message) const {
    return message.substr(header.length() + 1);
  }

  [[nodiscard]] inline const std::string &GetName() const { return name; }

private:
  std::string name;
  std::string header;
};

class OSIModel {
public:
  OSIModel()
      : layers{
            Layer("Application", "APP"), Layer("Presentation", "PRE"),
            Layer("Session", "SES"),     Layer("Transport", "TRA"),
            Layer("Network", "NET"),     Layer("Data Link", "DLI"),
            Layer("Physical", "PHY"),
        } {}

  const std::string Transfer(std::string message) {
    for (const auto &layer : this->layers) {
      std::cout << "Passing through " << layer.GetName() << " layer"
                << std::endl;

      message = layer.Transfer(message);
      std::cout << "message transferred: " << message << std::endl;
    }

    return message;
  }

  const std::string Receive(std::string message) {
    for (auto layer = layers.rbegin(); layer != layers.rend(); ++layer) {
      std::cout << "Passing through " << layer->GetName() << " layer"
                << std::endl;

      message = layer->Receive(message);
      std::cout << "message transferred: " << message << std::endl;
    }

    return message;
  }

private:
  std::array<Layer, 7> layers;
};

int main() {
  std::string message;
  std::cout << "Enter the message to be transferred: ";
  std::cin >> message;

  OSIModel model;

  std::string transferred = model.Transfer(message);
  std::string received = model.Receive(transferred);
  return 0;
}
