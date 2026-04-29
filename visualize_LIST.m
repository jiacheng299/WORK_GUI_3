function visualize_LIST( CLOSED,CLOSED_NUM,OPEN,OPEN_NUM,START,TARGET )
%VISUALIZE_CLOSED 此处显示有关此函数的摘要
%   此处显示详细说明
 
for i = 1:OPEN_NUM
    Open_Node = OPEN(i,:);
% %     %如果是Start_Node就不当作OpenNode画
% %     if Open_Node(1) == START(1) && Open_Node(2) == START(2)
% %         continue;
% %     %如果是Target_Node就不当作OpenNode画
% %     elseif Open_Node(1) == TARGET(1) && Open_Node(2) == TARGET(2)
% %         continue;
% %     end
    Open_Node_X = Open_Node(1);
    Open_Node_Y = Open_Node(2);
    plot(Open_Node_X,Open_Node_Y,'bs');
% %     fill([Open_Node_X,Open_Node_X,Open_Node_X-1,Open_Node_X-1,Open_Node_X],[Open_Node_Y,Open_Node_Y-1,Open_Node_Y-1,Open_Node_Y,Open_Node_Y],'red');   %%LIU:由当前OPEN(待探索)点开始按照正下，左下，正左，起始点的顺序围成一个正方形（矩形），并对其填充红色。
    %%fill([Open_Node_X-0.5,Open_Node_X-0.5,Open_Node_X+0.5,Open_Node_X+0.5],[Open_Node_Y+0.5,Open_Node_Y-0.5,Open_Node_Y-0.5,Open_Node_Y+0.5],'red');   %%LIU:由当前OPEN(待探索)点开始按照正下，左下，正左，起始点的顺序围成一个正方形（矩形），并对其填充红色。
    %%%LIU:scatter(Open_Node_X,Open_Node_Y,'red')  
% % %     plot(Open_Node_X,Open_Node_Y,'.','Color','r','MarkerSize',30);%%%LIU:plot(Open_Node_X,Open_Node_Y,'.','Color','g','MarkerSize',30);
    %%%LIU:scatter函数效率低，plot函数效率高。可能是因为scatter可实现的功能更花哨，如让点的大小和颜色有序变化，所以运行更慢。
end
 
for i = 1:CLOSED_NUM
    Close_Node = CLOSED(i,:);
% %     %如果是Start_Node就不当作CloseNode画
% %     if Close_Node(1) == START(1) && Close_Node(2) == START(2)
% %         continue;
% %     %如果是Target_Node就不当作CloseNode画
% %     elseif Close_Node(1) == TARGET(1) && Close_Node(2) == TARGET(2)
% %         continue;
% %     end
    Close_Node_X = Close_Node(1);
    Close_Node_Y = Close_Node(2);
    plot(Close_Node_X,Close_Node_Y,'g*');
    %%%fill([Close_Node_X-0.5,Close_Node_X-0.5,Close_Node_X+0.5,Close_Node_X+0.5],[Close_Node_Y+0.5,Close_Node_Y-0.5,Close_Node_Y-0.5,Close_Node_Y+0.5],'blue');
    %%fill([Close_Node_X,Close_Node_X,Close_Node_X-1,Close_Node_X-1,Close_Node_X],[Close_Node_Y,Close_Node_Y-1,Close_Node_Y-1,Close_Node_Y,Close_Node_Y],'blue');    %%LIU:由当前CLOSED(已访问)点开始按照正下，左下，正左，起始点的顺序围成一个正方形（矩形），并对其填充蓝色。
% % %     plot(Close_Node_X,Close_Node_Y,'.','Color','b','MarkerSize',30);%%%LIU:plot(Open_Node_X,Open_Node_Y,'.','Color','g','MarkerSize',30);
    %%%scatter(Close_Node_X,Close_Node_Y,'blue');
end
 
end
 