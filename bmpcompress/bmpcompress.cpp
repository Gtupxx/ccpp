/*
 * _______________#########_______________________ 
 * ______________############_____________________ 
 * ______________#############____________________ 
 * _____________##__###########___________________ 
 * ____________###__######_#####__________________ 
 * ____________###_#######___####_________________ 
 * ___________###__##########_####________________ 
 * __________####__###########_####_______________ 
 * ________#####___###########__#####_____________ 
 * _______######___###_########___#####___________ 
 * _______#####___###___########___######_________ 
 * ______######___###__###########___######_______ 
 * _____######___####_##############__######______ 
 * ____#######__#####################_#######_____ 
 * ____#######__##############################____ 
 * ___#######__######_#################_#######___ 
 * ___#######__######_######_#########___######___ 
 * ___#######____##__######___######_____######___ 
 * ___#######________######____#####_____#####____ 
 * ____######________#####_____#####_____####_____ 
 * _____#####________####______#####_____###______ 
 * ______#####______;###________###______#________ 
 * ________##_______####________####______________ 
 */

/*
 *                        _oo0oo_
 *                       o8888888o
 *                       88" . "88
 *                       (| -_- |)
 *                       0\  =  /0
 *                     ___/`---'\___
 *                   .' \\|     |// '.
 *                  / \\|||  :  |||// \
 *                 / _||||| -:- |||||- \
 *                |   | \\\  - /// |   |
 *                | \_|  ''\---/''  |_/ |
 *                \  .-\__  '-'  ___/-. /
 *              ___'. .'  /--.--\  `. .'___
 *           ."" '<  `.___\_<|>_/___.' >' "".
 *          | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *          \  \ `_.   \_ __\ /__ _/   .-` /  /
 *      =====`-.____`.___ \_____/___.-`___.-'=====
 *                        `=---='
 * 
 * 
 *      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *            佛祖保佑     永不宕机     永无BUG
 */

/*
 *  ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
 *  │Esc│   │ F1│ F2│ F3│ F4│ │ F5│ F6│ F7│ F8│ │ F9│F10│F11│F12│ │P/S│S L│P/B│  ┌┐    ┌┐    ┌┐
 *  └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘  └┘    └┘    └┘
 *  ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
 *  │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ BacSp │ │Ins│Hom│PUp│ │N L│ / │ * │ - │
 *  ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
 *  │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│ | \ │ │Del│End│PDn│ │ 7 │ 8 │ 9 │   │
 *  ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤ + │
 *  │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│ Enter  │               │ 4 │ 5 │ 6 │   │
 *  ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤
 *  │ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│  Shift   │     │ ↑ │     │ 1 │ 2 │ 3 │   │
 *  ├─────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤ E││
 *  │ Ctrl│    │Alt │         Space         │ Alt│    │    │Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │←─┘│
 *  └─────┴────┴────┴───────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
 */

/*
 *  ┌─────────────────────────────────────────────────────────────┐
 *  │┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐│
 *  ││Esc│!1 │@2 │#3 │$4 │%5 │^6 │&7 │*8 │(9 │)0 │_- │+= │|\ │`~ ││
 *  │├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤│
 *  ││ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{[ │}] │ BS  ││
 *  │├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤│
 *  ││ Ctrl │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│ Enter  ││
 *  │├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤│
 *  ││ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│Shift │Fn ││
 *  │└─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴──┬┴───┴┬──┴┬─────┴───┘│
 *  │      │Fn │ Alt │         Space         │ Alt │Win│   HHKB   │
 *  │      └───┴─────┴───────────────────────┴─────┴───┘          │
 *  └─────────────────────────────────────────────────────────────┘
 */

/*
 * @Author: 柚岩龙蜥 1152349903@qq.com
 * @Date: 2023-04-25 22:04:24
 * @LastEditors: 柚岩龙蜥 1152349903@qq.com
 * @LastEditTime: 2023-05-03 22:33:23
 * @FilePath: \ccpp\bmpcompress\bmpcompress.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <functional>

using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

const string before = "1.bmp";
const string after = "2.bmp";

struct huftree
{
    int cnt;
    char uch;
    huftree *l;
    huftree *r;
    huftree(int _cnt, char _uch)
    {
        cnt = _cnt;
        uch = _uch;
        l = nullptr;
        r = nullptr;
    }
};
class compress
{
public:
    compress(std::ifstream &file)
    {
        char uch;
        while (file.eof() == false)
        {
            file.read((char *)&uch, sizeof(char));
            m_content.push_back(uch);
            m_freq[uch]++;
        }
        file.close();
    }

    void encode(std::ofstream &output)
    {
        cout << "encode started !\n";
        cout << "bulding huffman tree...\n";
        this->build();
        string ans;
        cout << "encoding...\n";
        for (auto uch : m_content)
        {
            ans.append(m_code[uch]);
        }
        output << ans;
        output.close();
        cout << "encode finished !\n";
        float compressibility = 0.0f;
        int bef = m_content.size() * 8;
        int aft = (0 - ans.size()) % 8 + ans.size();
        compressibility = 100.0f * (float)aft / (float)bef;
        cout << "the compressibility is : " << compressibility << "% !\n";
    }

    void decode(std::ifstream &input, std::ofstream &output)
    {
        cout << "decode started !\n";
        string in;
        char ch;
        while (input.eof() == false)
        {
            input >> ch;
            in.push_back(ch);
            for (auto [uch, co] : m_code)
            {
                if (co == in)
                {
                    output.write((char *)(&uch), sizeof(char));
                    in.clear();
                    break;
                }
            }
        }
        input.close();
        output.close();
        cout << "decode finished !\n";
    }
    
    void out(std::ofstream &output)
    {
        for (auto uch : m_content)
        {
            output.write((char *)(&uch), sizeof(char));
        }
        output.close();
    }

    void treout()
    {
        std::ofstream output("tree.txt", std::ios::ate);
        vector<std::pair<int, string>> vec;
        for (auto [ch, str] : m_code)
        {
            vec.push_back({(int)(unsigned char)ch, str});
        }
        std::sort(vec.begin(), vec.end(), [](std::pair<int, string> a, std::pair<int, string> b)
                  { return a.first < b.first; });
        for (auto [key, val] : vec)
        {
            output << "key:  " << key << "\t val: " << val << std::endl;
        }
    }

    void conout()
    {
        std::ofstream output("content.txt", std::ios::ate);
        for(auto ch:m_content)
        {
            output << (int)(unsigned char)ch << ' ';
        }
    }

private:
    void build()
    {
        vector<huftree *> huf;
        for (auto [uch, cnt] : m_freq)
        {
            huf.push_back(new huftree(cnt, uch));
        }
        while (huf.size() > 1)
        {
            sort(huf.begin(), huf.end(), [](huftree *a, huftree *b)
                 { return a->cnt > b->cnt; });
            int tcnt = huf[huf.size() - 1]->cnt + huf[huf.size() - 2]->cnt;
            huftree *temp = new huftree(tcnt, '0');
            temp->l = huf[huf.size() - 1];
            temp->r = huf[huf.size() - 2];
            huf.pop_back();
            huf.pop_back();
            huf.push_back(temp);
        }
        string ncode = "";
        std::function<void(huftree *)> dfs;
        dfs = [&](huftree *t)
        {
            if (t->l == nullptr)
            {
                m_code[t->uch] = ncode;
                return;
            }
            ncode.push_back('0');
            dfs(t->l);
            ncode.pop_back();
            ncode.push_back('1');
            dfs(t->r);
            ncode.pop_back();
        };
        dfs(huf[0]);
    }

private:
    vector<char> m_content;
    unordered_map<char, int> m_freq;
    unordered_map<char, string> m_code;
};

int main()
{
    std::ifstream ibmp(before, std::ios::binary | std::ios::in);
    std::ofstream obmp(after, std::ios::ate | std::ios::binary);
    if (ibmp.is_open() == false)
    {
        cout << "failed to open the file !\n";
        return 0;
    }
    compress cmp(ibmp);

    std::ofstream otxt("data.txt", std::ios::ate);
    cmp.encode(otxt);
    std::ifstream itxt("data.txt", std::ios::in);
    cmp.treout();
    cmp.conout();
    cmp.out(obmp);
    system("pause");
    return 0;
}