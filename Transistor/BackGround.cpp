
#include "BackGround.h"

void printBackGround()				//打印背景故事
{
	system("cls");

	int x = 15;
	int y = 7;
	gotoXY(x++, y); cout << "故事发生在一个叫做Cloudbank(云堤)的城市中，玩家控制城市中很出名的歌手Blue，在一次公开演出时Camerata成员企图用Transistor袭击Blue,"; _sleep(150);
	gotoXY(x++, y); cout << "Blue男友帮其挡下致命一击，他的灵魂跟人格被上传到Transistor中，通过Camerata成员的留言信息，Blue发现Transistor是Camerata制造出来控"; _sleep(150);
	gotoXY(x++, y); cout << "制Process（处理器）的，但是袭击Blue失败，导致Transistor被夺走，Process失控。当Camerata发现计划失败想拿回Transistor来挽回一切，但"; _sleep(150);
	gotoXY(x++, y); cout << "是太迟，只有Royce想将计划执行到底。。。（后来在旅程中逐渐得知自己手中的剑Transistor并不是一把真正意义的剑，而是一把作用非凡但来"; _sleep(150);
	gotoXY(x++, y); cout << "源不明的剑型武器。）"; _sleep(150);

	_getch();
}


void printGameOver()
{
	system("cls");

	gotoXY(10, 10);
	cout << "                        .,i7LLv,                                                                                                              " << endl;
	cout << "                   :::7XEZZ8MMB@X:                                                                                                            " << endl;
	cout << "                 .v188SjZOBO0PMB@Br                                                                                                           " << endl;
	cout << "                11uLjMB@Gqvi:r7777                                                                                                            " << endl;
	cout << "               7viFM@B0:                                                                                                                      " << endl;
	cout << "             iULrPB@P.                                                                             ....                                       " << endl;
	cout << "            22rLB@@i                                                      ,ir       .v5F205,      vX8O@BE                                     " << endl;
	cout << "           ,L;j@BB                   ::r.           :7XEEE0MOEi          :SZB@;    .JY5ZNM@@@:   vvvZvP@BB.                 jYuEOO8MMO:       " << endl;
	cout << "           7v:0B@.           .7UqqGGE0OM@B1      ,uX87YGGN80OB@E:        .LiZB@   7u7vOEE2iO@@  LvrG@::q@@@.             :UuUSE0MOZX8B@k      " << endl;
	cout << "          ,UiuB@5      iJq0NNZkjJkkP2PqGB@B     .UJvSEq@BSYuu2EBB@L      .L:2@B. LJ7JZB@ui:2B@Gi7i5@Br:iZ@BO            7YLqG@BOU7:L7rG@:     " << endl;
	cout << "          :v:k@B,     75U1PXqNZNPXSJEENSur     :uvrF@BOY.    i7iUB@F      L:JB@;,7r0MM@i ,7:ZBBi:v@BB:r:7M@@:         .L7vG@@u    .iiL@B.     " << endl;
	cout << "          i7iGB@      r1u50@B@MSU2iv@@        iPYiU@@G        r:v@BL      ri7@BEi:;MB@r   7iu@J:iOB@v r7:0B@7        :J7UBB2   .rjLjq@B7      " << endl;
	cout << "          7riZ@@      :Y22OZr   ,7iu@B;       j7vX@BE        ,v:1B@i      rrrM@u::GB@L    viY@i:GB@5  :v:2@Bv        vru@Br .ruY2GkB@B.       " << endl;
	cout << "          r7:EB@,                vivB@L       Lir@B@        .Lri0@B,      iv:MB7.JB@Z     ir7F:1B@B   .J:JM@M.   uOMPrr@BXrJ2kk0B@@Ui         " << endl;
	cout << "          i7:5@Bk                ;ri@@@:      jivB@8       :1771OB@       :v:NO:iO@B,     r7riLB@Bi   ,LivMO@i  v21EZU0ZYv1SGM@BO,            " << endl;
	cout << "          ,ji7B@B:               :r:S@B7     ,Jiu@BP      ,ur7GNL@@       .LiF5:k@B:      ivi7MBBX    .YiLOOB1  i5Pkv7ZkSG88POj.         :i   " << endl;
	cout << "           LLi1B@Bv              7v:SB@      .jiSB@      .Yi7O@i7B@rrXF   .vrYLr@B8       iviU@BO     .L;;MM@S     .viZB0             ,YLq@:  " << endl;
	cout << "           ,ju;LM@BZ:        ,rY2LiLB@B.      iY7@BJ   .rjr5M@O:rOZ@7E@;   vr7ikB@v       :L:1B@q     .Li:0@Bk      r7Y@@:       :ru1PuZZPBO  " << endl;
	cout << "             ruLJuOB@BOSSuFENSX5kkSG@BE        rLv0@@v72uYGB@L:;i7M@Uv@F   7v:vM@@.       iYiF@BJ     .L7:NB@O      .L71M@@Zk115XkPkPP0O@B@U  " << endl;
	cout << "              .7JYJ5SZZ88M5uk0E8M@B85:          iLrPBqjF0@B@;  JLrvBB@Z    LJrJ@B@        .uY5B@.      JJ7F@B@       ,YUjFPZZ80qXqEMB@B8Y,    " << endl;
	cout << "                 rUFqqEE88OZMB@SF7               :2FGEMB@Mv     7jJB@O      Y5k@@r          7uOE        v2kB@r         ,Y2qZOZOOBM85v.        " << endl;
	cout << "                    ..,::i::ir                     ,:;i:.        ,Uki        .rU:                          :.             .i::..              " << endl;
	cout << endl;
	cout << endl;
	cout << "                                  :. :                                                                                              " << endl;
	cout << "                               ,L5E@E@N7uuEMYi,                                                                                     " << endl;
	cout << "                             :u2JL5EkOMuZk0M@B@Br                                                                                   " << endl;
	cout << "                           .v1L1FPNU:POGMOXPF2Z@@O.                                                                                 " << endl;
	cout << "                           vY:1B@G2LSB@OJ::rL7rYBB@        .                 .                                                      " << endl;
	cout << "                          vY;5B@M  rJJ:      :Li7@BBr     rMB0U            :uOMF.                .   .                     ::       " << endl;
	cout << "                         L17L@@F              :LivBB@i    :LUB@@           7uvM@@            ,SuXGM8OM@Bi        ..    :UEk0@BMi    " << endl;
	cout << "                        iu:UB@N                i7:Y@@@     Y;LB@B          virO@@          vF5jXEOMOqS0@@G    .vFMBv jX1LP1FqMB@.   " << endl;
	cout << "                        Jri8@B.                 Lr:N@Bj    ,YijB@q       .ur7Z@@:        .YvJ0BBBU7,,v7i@B.  .Pu7M@Birru0M@MON@@:   " << endl;
	cout << "                       :LiL@BF                  :L:LB@B     iLiX@@i     .Ur7M@B,        :jruM@Br    ,ri5B@    7viOB0:i5@B@L.        " << endl;
	cout << "                       7v:Z@@:                  .Li7BB@.     77iBB@     Y7iG@Bi        iurNB@i   :YujuMB@.    :viu@7:X@BO           " << endl;
	cout << "                      .urrM@B                   .L:7M@B.      viv@Bj   uLi2@BX      . ,viqB@, :LuJFMP@BN       LrrOr5@BZ            " << endl;
	cout << "                       vriBB@                   ;v:v@B@       :v:S@B. :vijBB@     .UOMNiv@Mj7u5kNO@BMr.        :Yi7S@B@             " << endl;
	cout << "                      .urrB@B                  ,LrrMB@i        LvLq@M.;riB@@.     u55ZPU0NLuS0O@B@U             Lr:M@@7             " << endl;
	cout << "                      .u7:OB@7                rJri8@@v         :k77B@P::1B@F      r2kU778SNNZPFNi          L;   77:5@BG             " << endl;
	cout << "                       :Yr7MB@r             :uY7uMB@S           .Jiu@P.vM@@          .vrO@v             iSvMB,  ,v:vB@M             " << endl;
	cout << "                        rur7MB@v.        .7jU7UG@BM:             .LiEE:G@B:           7r1@Mi      ,iLUPq2EqN@S   vi;BB@             " << endl;
	cout << "                         iuLvZO@BOPkU12PqPUkSGB@Oi                iL7uv@B8            .urFO@MMZ0PXkXkXX0G@B@O7   vriX@Br            " << endl;
	cout << "                           rSuUU00GOONZEMMOB@G0i                   iJiuB@j             .Juu5q0G0EXq0MM@BMFi      rJikB@j            " << endl;
	cout << "                              :uk0GOZOM8PO1::                       ;1k@B.               ,v1kGGO8M8ZSU:.         .v5O@B.            " << endl;
	cout << "                                 .. :.                               .rL,                    ,.                     i,  " << endl;
}

