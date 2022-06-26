# HS_SPR_CAL
Hearthstone Spectral Pillager Rogue Calculator
炉石鬼灵贼计算器 持续更新中

使用说明

BF.cpp输出最大伤害

APP.cpp可以输出最大伤害和方案，且可以设置：伤害超出特定值（修改int eh=）或者到达时间限制（修改int tlim=）就立即输出

以上两者需要手动修改samplecons()内的代码以设置局面

**新增** APP.cpp目前改成了运行时读取局面和伤害限界的版本，也可以手动修改为sample1=sample1cons()进行回退

同时为了方便测试性使用，将APP.cpp的编译结果APP.exe上传（固定tlim=999999），**注意**这个版本的算法效率非常低，比较复杂的局面可能就跑不出来（现在不吃内存了），发现跑不出来请自行掐掉

**声明**作者不对运行APP.exe产生的任何后果负责，如果不信任请自行生成编译结果

输入格式：

伤害限界（一般为血量，不想设置限界的话可以设置为999999）

手牌数量

手牌1中文缩写 手牌1费用

...

手牌n中文缩写 手牌n费用

（友方）随从数量（可以为0，如果是0的话下一部分就直接略去了）

随从1中文缩写

...

随从n中文缩写

（目前的缩写列表：ayb,bc,jb,sjdf,hjys,syzl,hrlq,dy,tw,glfz,ljsc,ljfs,lj）

伺机待发累计数 狐人老千累计数 刀油下第一张累计数 刀油下第二张累计数（光环；范围分别是0-1,0-3,0-2,0-2；如果是回合开始时就应该是0 0 0 0）

剩余费用

本回合已经打出过的卡牌数量（如果是回合开始时就应该是0）

输入例子（不包括最开始的知情y）：

```
10
4
hrlq 2
dy 4
glfz 6
glfz 6
1
syzl
0 0 0 0
2
0
```

这个例子表示伤害限界为10，手牌为2费狐人老千，4费刀油，6费鬼灵匪贼，6费鬼灵贼，（友方）随从为鲨鱼之灵，光环为全0，剩余费用为2，已打出数量为0

AUTO.cpp可以在炉石运行期间自动从.log文件中读取手牌和费用并生成局面（路径需手动修改；使用不要过于频繁，有理论封号可能），目前仅能支持在回合开始时一张牌都还没出的时间点（且在此时主动运行程序）自动读取，其他时间点读取都有可能是错误结果

考虑范围与一些约定可见下方

强调：目前不支持随从血量，这部分影响了有关背刺的判断

目前支持背刺，且假定腾格子时只需背刺老千和腾武，用作打连击时可不指定地任意打出

修复：（这次真的）目前已经支持空场使用赤烟腾武了

修复：AUTO.cpp的自动读入似乎更正确了（尽管代码更奇怪了），（未经测试地）能够支持另一情况：背刺用作打连击时不在能任意打出，而需要存在友方场上任意的鲨鱼之灵、刀油、鬼灵匪贼。

**编译选项**：-g -std=c++11 -O2

</br>

当前考虑范围：

对手空场（**待定**，影响背刺是否具有合理目标）且无干扰因素（**待定**，但短期内不可能考虑干扰因素），己方可能已控制若干随从，己方可能已打出若干卡牌（已经进行了一些过牌）

己方必须在当前回合借助手牌和剩余费用斩杀

己方可能的手牌：暗影步，背刺，伪造的幸运币，伺机待发，幻觉药水，鲨鱼之灵，狐人老千，斯卡布斯·刀油，赤烟·腾武，鬼灵匪贼（**待定**：垃圾（随从），垃圾（非随从，但也许可以补充伤害），垃圾（不可用））

（优化倾向：通常来说，不会有过多同名手牌）

己方可能的随从（范围等同于手牌的随从牌）：鲨鱼之灵，狐人老千，斯卡布斯·刀油，赤烟·腾武，鬼灵匪贼（**待定**，垃圾）

手牌的费用（光环减费前）：重要，随从包括原费，-2费（暗影步），=1费（腾武或幻觉药水）三种情形，法术可能减少了任意费用

手牌的顺序：无关

手牌的随从牌的血量（原血或1血）：重要性待定，影响被使用后的随从的血量

随从的顺序：**重要性待定**，影响手牌数量过多时的幻觉药水（根据经验，较少出现：因为随从顺序真正影响了能否斩杀）

随从的血量（原血或1血，若为原血还可能有受伤量）：**重要性待定**，影响能否被背刺或鬼灵匪贼去除（根据经验，几乎不会出现：需要用背刺或鬼灵匪贼去除，但因实际无法去除而导致斩杀失败）

手牌数量上限固定为10，随从数量上限固定为7，剩余费用上限固定为10

</br>

因为种种原因，考虑用C++实现

手牌应当用hands=set<name,cost(,health)>描述

随从应当用minions=set or list<name(,health)>描述

光环减费应当用s1,s2,s3,s4描述，分别表示伺机待发累计（0-1），狐人老千累计（0-3），刀油第一张累计（0-2），刀油第二张累计（0-2）

剩余费用应当用mana描述

已打出卡牌数量应当用num描述

一个当前状态(state)应当包含以上这些；对于一个当前状态，优化目标为（对敌方英雄造成的）最大伤害(maxdmg)

一项操作(ope)用name或name,target表示（target当：name为背刺，暗影步，腾武时，取某一随从；name为鬼灵匪贼时，取敌方英雄或某一随从）

一系列操作用opes=list<ope>表示
  
</br>

应有基础函数：trans(state,ope)->(state,dmg)，**待定**：因为dmg具有可加性，可以设计为被各项操作分离（参考马尔可夫决策过程中，因为收益具有可加性，而被各次决策分离）

可以写出Brute Force：maxdmg(state):=max(ope of allope(state))(trans.dmg+maxdmg(trans.state)),where trans=trans(state,ope)

</br>

**2022/5/15会议纪要**

干扰因素不考虑

暗歌补充：随机性过牌不考虑

对手空场：暗歌认为考虑

垃圾：考虑

随从顺序：暗歌认为考虑

随从血量：暗歌认为假设背刺和鬼灵匪贼总能去除

明确两个模式：1.最大化伤害 2.伤害达到血量即可

</br>

**2022/5/22会议纪要**

暗歌再次强调：考虑超凡

奶青 复盘为主，实战演算为辅

凌果冰 背刺如要凑连击，几乎只有起手困难

背刺如要腾格子，几乎只需要给老千和腾武

桉 如有需要，背刺总能腾出格子

开始收集鬼灵题目图片

提及补丁优先级

</br>

**2022/5/29会议纪要**

估计伤害上限以剪枝：

1.用张数和鬼数估计伤害上限

2.仅用公式的最高伤害乘以一定倍数（例如2）

算法抉择：广度优先搜索；深度优先搜索+分支限界

人工优化：<10费时先用硬币

UI：先鸽着

极限情况：“6+4”

公式优化：在做了

