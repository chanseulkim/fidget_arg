
#include <iostream>
#include <unordered_map>
#include <memory>
#include <functional>

namespace fidget_param
{
    template <typename T>
    class fidget_arg
    {
    public:
        fidget_arg() {}
        virtual ~fidget_arg() {}

        void push(const std::string &key, std::function<void(T *)> fn) {
            funcs[key] = std::make_shared<std::function<void(T *)>>(fn);
        }
        void parse(int argc, char** argv) {
            for (size_t i = 1; i < argc; i++) {
                //printf("[debug] arg : %s\n", argv[i]);
                work(argv[i]);
            }
        }
        void work(const std::string &key) {
            if (funcs.find(key) == funcs.end()) {
                return;
            }
            (*funcs[key])(nullptr);
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<std::function<void(T *)>>> funcs;
    };

}
struct gconfig {
    std::string name;
    int number;
    std::string name2;
    int number2;
};

template <typename T>
void init(fidget_param::fidget_arg<T>& fg, T& conf) {
    std::function<void(T*)> fn_s = [](T* _conf) {
        gconfig* config = static_cast<gconfig*>(_conf);
        config->name = "fn_s";
        config->number = 1;
    };
    std::function<void(T*)> fn_d = [](T* _conf) {
        gconfig* config = static_cast<gconfig*>(_conf);
        config->name2 = "fn_d ";
        config->number2 = 2;
    };
    fg.push("-s", std::bind(fn_s, &conf));
    fg.push("-d", std::bind(fn_d, &conf));
}

int main(int argc, char** argv){
    fidget_param::fidget_arg<gconfig > fg;
    gconfig conf;
    init<gconfig>(fg, conf);

    fg.parse(argc, argv);

    printf("hello config name : %s\n", conf.name.c_str());
    printf("hello config number : %d\n", conf.number);
    printf("hello config name2 : %s\n", conf.name2.c_str());
    printf("hello config number2 : %d\n", conf.number2);
    return 0;
}