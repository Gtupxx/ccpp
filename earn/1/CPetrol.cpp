#include <iostream>
using namespace std;
class CPetrol
{
public:
    CPetrol(float _P_90 = 0.0f, float _P_93 = 0.0f, float _P_98 = 0.0f, float _V_90 = 0.0f, float _V_93 = 0.0f, float _V_98 = 0.0f)
        : P_90(_P_90), P_93(_P_93), P_98(_P_98), V_90(_V_90), V_93(_V_93), V_98(_V_98) {}

    // 下面是设置价格函数
    void setPrise_90(float _P_90)
    {
        P_90 = _P_90;
    }
    void setPrise_93(float _P_93)
    {
        P_93 = _P_93;
    }
    void setPrise_98(float _P_98)
    {
        P_98 = _P_98;
    }

    // 下面是设置油量函数
    void setVolume_90(float _V_90)
    {
        V_90 = _V_90;
    }
    void setVolume_93(float _V_93)
    {
        V_93 = _V_93;
    }
    void setVolume_98(float _V_98)
    {
        V_98 = _V_98;
    }

    // 求总价函数
    float getTotal()
    {
        float ans = 0.0f;
        ans += V_90 * P_90;
        ans += V_93 * P_93;
        ans += V_98 * P_98;
        return ans;
    }

private:
    float P_90 = 0.0f;
    float P_93 = 0.0f;
    float P_98 = 0.0f;
    float V_90 = 0.0f;
    float V_93 = 0.0f;
    float V_98 = 0.0f;
};

int main()
{
    CPetrol a(1.2, 1.5, 1.9, 2, 2, 2);
    cout << a.getTotal();
}