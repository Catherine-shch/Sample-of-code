#include <iostream>
#include <vector>
// Классы всех возможных основ под тесто
class Thick_crust
{
public:
    void info() {
        std::cout << "thick crust" << "\n";
    }
};
class Thin_crust
{
public:
    void info() {
        std::cout << "thin crust" << "\n";
    }
};
// Классы всех возможных соусов
class Tomato
{
public:
    void info() {
        std::cout << "tomato" << "\n";
    }
};
class Cream
{
public:
    void info() {
        std::cout << "cream" << "\n";
    }
};
class Pesto
{
public:
    void info() {
        std::cout << "pesto" << "\n";
    }
};
class Spicy
{
public:
    void info() {
        std::cout << "spicy" << "\n";
    }
};
class Garlic
{
public:
    void info() {
        std::cout << "garlic" << "\n";
    }
};
//Добавки 
class ham
{
public:
    void info() {
        std::cout << "ham" << "\n";
    }
};
class cheese
{
public:
    void info() {
        std::cout << "cheese" << "\n";
    }
};
class mushrooms
{
public:
    void info() {
        std::cout << "mushrooms" << "\n";
    }
};
class olives
{
public:
    void info() {
        std::cout << "olives" << "\n";
    }
};
class onion
{
public:
    void info() {
        std::cout << "onion" << "\n";
    }
};

// Класс "Пицца", содержащий все типы теста, соусов и добавок
class Pizza
{
public:
    std::vector<Thick_crust> tk;
    std::vector<Thin_crust> tn;
    std::vector<Tomato> to;
    std::vector<Cream> cr;
    std::vector<Pesto> pe;
    std::vector<Spicy> sp;
    std::vector<Garlic> ga;
    std::vector<ham> ha;
    std::vector<cheese> ch;
    std::vector<mushrooms> mu;
    std::vector<olives> ol;
    std::vector<onion> on;
    void info() {
        int i;
        for (i = 0; i < tk.size(); ++i) tk[i].info();
        for (i = 0; i < tn.size(); ++i) tn[i].info();
        for (i = 0; i < to.size(); ++i) to[i].info();
        for (i = 0; i < cr.size(); ++i) cr[i].info();
        for (i = 0; i < pe.size(); ++i) pe[i].info();
        for (i = 0; i < sp.size(); ++i) sp[i].info();
        for (i = 0; i < ga.size(); ++i) ga[i].info();
        for (i = 0; i < ha.size(); ++i) ha[i].info();
        for (i = 0; i < ch.size(); ++i) ch[i].info();
        for (i = 0; i < mu.size(); ++i) mu[i].info();
        for (i = 0; i < ol.size(); ++i) ol[i].info();
        for (i = 0; i < on.size(); ++i) on[i].info();
    }
};
// Базовый класс Pizza объявляет интерфейс для поэтапного
// построения пиццы и предусматривает его реализацию по умолчанию
class PizzaBuilder
{
protected:
    Pizza* p;
public:
    PizzaBuilder() : p(0) {}
    virtual ~PizzaBuilder() {}
    virtual void createPizza() {}
    virtual void buildThick_crust() {}
    virtual void buildThin_crust() {}
    virtual void buildTomato() {}
    virtual void buildCream() {}
    virtual void buildPesto() {}
    virtual void buildSpicy() {}
    virtual void buildGarlic() {}
    virtual void buildham() {}
    virtual void buildcheese() {}
    virtual void buildmushrooms() {}
    virtual void buildolives() {}
    virtual void buildonion() {}
    virtual Pizza* getPizza() { return p; }
};
// Margherita
class MargheritaBuilder : public PizzaBuilder
{
public:
    void createPizza() { p = new Pizza; }
    void buildThick_crust() { p->tk.push_back(Thick_crust()); }
    void buildTomato() { p->to.push_back(Tomato()); }
    void buildcheese() { p->ch.push_back(cheese()); }
};
// Pizza_al_Pesto
class Pizza_al_PestoBuilder : public PizzaBuilder
{
public:
    void createPizza() { p = new Pizza; }
    void buildThick_crust() { p->tk.push_back(Thick_crust()); }
    void buildPesto() { p->pe.push_back(Pesto()); }
    void buildcheese() { p->ch.push_back(cheese()); }
    void buildolives() { p->ol.push_back(olives()); }
};
//Quattro Stagioni
class Quattro_StagioniBuilder : public PizzaBuilder
{
public:
    void createPizza() { p = new Pizza; }
    void buildThick_crust() { p->tn.push_back(Thin_crust()); }
    void buildTomato() { p->to.push_back(Tomato()); }
    void buildCream() { p->cr.push_back(Cream()); }
    void buildcheese() { p->ch.push_back(cheese()); }
    void buildham() { p->ha.push_back(ham()); }
    void buildmushrooms() { p->mu.push_back(mushrooms()); }
    void buildolives() { p->ol.push_back(olives()); }
};
//Sarda
class SardaBuilder : public PizzaBuilder
{
public:
    void createPizza() { p = new Pizza; }
    void buildThick_crust() { p->tn.push_back(Thin_crust()); }
    void buildSpicy() { p->sp.push_back(Spicy()); }
    void buildGarlic() { p->ga.push_back(Garlic()); }
    void buildcheese() { p->ch.push_back(cheese()); }
    void buildham() { p->ha.push_back(ham()); }
    void buildonion() { p->on.push_back(onion()); }
};
// Класс-распорядитель, поэтапно создающий пиццу разных видов.
// здесь определен алгоритм построения пиццы.
class Director
{
public:
    Pizza* createPizza(PizzaBuilder& builder)
    {
        builder.createPizza();
        builder.buildThick_crust();
        builder.buildThin_crust();
        builder.buildTomato();
        builder.buildCream();
        builder.buildPesto();
        builder.buildSpicy();
        builder.buildGarlic();
        builder.buildham();
        builder.buildcheese();
        builder.buildmushrooms();
        builder.buildolives();
        builder.buildonion();
        return(builder.getPizza());
    }
};
int main()
{
    Director dir;
    MargheritaBuilder ma_builder;
    Pizza_al_PestoBuilder ap_builder;
    Quattro_StagioniBuilder qs_builder;
    SardaBuilder sa_builder;
    Pizza* ma = dir.createPizza(ma_builder);
    Pizza* ap = dir.createPizza(ap_builder);
    Pizza* qs = dir.createPizza(qs_builder);
    Pizza* sa = dir.createPizza(sa_builder);
    std::cout << "Margherita:" << "\n";
    ma->info();
    std::cout << "\nPizza al Pesto:" << "\n";
    ap->info();
    std::cout << "\nQuattro Stagioni:" << "\n";
    qs->info();
    std::cout << "\nSarda:" << "\n";
    sa->info();
    return 0;
}