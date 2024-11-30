#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <optional>
#include <sstream>

using namespace std;

using AttrMap = unordered_map<string, string>;

class Node; 

//data for each element or tag - functions to get id and classes and store other attributes
class ElementData {
public:
    string tag_name;
    AttrMap attrs;

    ElementData(const string& tag_name, const AttrMap& attrs)
        : tag_name(tag_name), attrs(attrs) {}

    optional<string> id() const {
        auto it = attrs.find("id");
        if (it != attrs.end()) {
            return it->second;
        }
        return nullopt;
    }

    unordered_set<string> classes() const {
        unordered_set<string> class_set;
        auto it = attrs.find("class");
        if (it != attrs.end()) {
            istringstream stream(it->second);
            string class_name;
            while (stream >> class_name) {
                class_set.insert(class_name);
            }
        }
        return class_set;
    }
};

enum class NodeType {
    Element,
    Text
};

// Node Class
class Node {
public:
    vector<shared_ptr<Node>> children;
    NodeType node_type;
    shared_ptr<ElementData> element_data;
    string text_data;                    

    Node(const string& text)
        : node_type(NodeType::Text), text_data(text) {}

    Node(const string& tag_name, const AttrMap& attrs, const vector<shared_ptr<Node>>& children)
        : node_type(NodeType::Element),
          element_data(make_shared<ElementData>(tag_name, attrs)),
          children(children) {}
};

shared_ptr<Node> text(const string& data) {
    return make_shared<Node>(data);
}

shared_ptr<Node> elem(const string& tag_name, const AttrMap& attrs, const vector<shared_ptr<Node>>& children) {
    return make_shared<Node>(tag_name, attrs, children);
}
