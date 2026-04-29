function visualize_map(map,xStart,yStart,xTarget,yTarget, MAX_X, MAX_Y,lead_node_num,real,device)
%This function visualizes the 2D grid map 
%consist of obstacles/start point/target point/optimal path.
set(gca, 'XTick', 0:1:MAX_X);  %%LIU:set(gca,'xtick',坐标刻度):自定义坐标刻度
set(gca, 'YTick', 0:1:MAX_Y);
grid on;
% grid minor;
axis equal;  %%LIU:设置屏幕高宽比，使得每个坐标轴都具有均匀的刻度间隔        
axis ([0 MAX_X 0 MAX_Y ]);  %%LIU:axis([xmin xmax ymin ymax])函数:设置当前二维图形对象的 x 轴 和 y 轴的取值范围。向量参数[xmin xmax ymin ymax] 中的元素分别表示 x 轴最小值、x 轴最大值、y 轴最小值和 y 轴最大值。
hold on;  %%LIU:hold on是当前轴及图像保持而不被刷新，准备接受此后将绘制的图形，多图共存

% % % ytick = get(gca,'ytick');
% % % yticklabel = get(gca,'yticklabel');
% % % yticklabelN = mat2cell(num2str(8*cellfun(@str2num,yticklabel)),ones(length(ytick),1)); % 将y轴标注放大10倍
% % % yticklabels(yticklabelN)

% obstacles
% % % plot(map(2:size(map, 1) - 1,1),map(2:size(map, 1) - 1,2),'g-','LineWidth',3);

% % for obs_cnt = 2: size(map, 1) - 1
% %     fill([map(obs_cnt, 1),map(obs_cnt, 1),map(obs_cnt, 1)-1,map(obs_cnt, 1)-1,map(obs_cnt, 1)],...  %%LIU:...为续行符，当一行内语句太长，可以使用三个点...表示续行，另起一行。
% %          [map(obs_cnt, 2),map(obs_cnt, 2)-1,map(obs_cnt, 2)-1,map(obs_cnt, 2),map(obs_cnt, 2)],'k');  %%LIU:fill(x,y,'r')函数：数组x，数组y内元素分别对应组成坐标点，因此，此行应该与上一行对照看，按列看，每列为一组点的坐标，因此相当于是由当前点开始按照正下，左下，正左，当前点的顺序围成一个正方形（矩形），并对其填充黑色。因此，只有黑色方块右上角点为实际的障碍点。
% %     hold on;
% % end
% start point
% % fill([map(1, 1),map(1, 1),map(1, 1)-1,map(1, 1)-1,map(1, 1)],...
% %      [map(1, 2),map(1, 2)-1,map(1, 2)-1,map(1, 2),map(1, 2)],'y');  %%LIU:由起始点开始按照正下，左下，正左，起始点的顺序围成一个正方形（矩形），并对其填充黄色。因此，只有黄色方块右上角点为实际的起始点。
fill([xStart-0.2,xStart+0.2,xStart+0.2,xStart-0.2],...
     [yStart+0.2,yStart+0.2,yStart-0.2,yStart-0.2],'y');
hold on;
% target point
fill([xTarget-0.2,xTarget+0.2,xTarget+0.2,xTarget-0.2],...
     [yTarget+0.2,yTarget+0.2,yTarget-0.2,yTarget-0.2],'g');  %%LIU:由目标点开始按照正下，左下，正左，起始点的顺序围成一个正方形（矩形），并对其填充绿色。因此，只有绿色方块右上角点为实际的目标点。
hold on;

% % % fill([map(1, 1)-0.2,map(1, 1)+0.2,map(1, 1)+0.2,map(1, 1)-0.2],...
% % %      [map(1, 2)+0.2,map(1, 2)+0.2,map(1, 2)-0.2,map(1, 2)-0.2],'y');
% % % hold on;
% % % % target point
% % % fill([map(size(map, 1))-0.2,map(size(map, 1))+0.2,map(size(map, 1))+0.2,map(size(map, 1))-0.2],...
% % %      [map(size(map, 1), 2)+0.2,map(size(map, 1), 2)+0.2,map(size(map, 1), 2)-0.2,map(size(map, 1), 2)-0.2],'g');  %%LIU:由目标点开始按照正下，左下，正左，起始点的顺序围成一个正方形（矩形），并对其填充绿色。因此，只有绿色方块右上角点为实际的目标点。
% % % hold on;
%%
%%LIU:新加连线
%%%plot(map(:,1),map(:,2),'g-','LineWidth',3);

% % 0606 
% % % obstacle
% % % a=[14 15;14 16;14 17;14 18;14 19;15 15;15 16;15 17;15 18;15 19;16 15;16 16;16 17;16 18;16 19;17 15;17 16;17 17;17 18;17 19];
% % % for i=1:size(a, 1)
% % % fill([a(i, 1),a(i, 1),a(i, 1)-1,a(i, 1)-1,a(i, 1)],...
% % %      [a(i, 2),a(i, 2)-1,a(i, 2)-1,a(i, 2),a(i, 2)],'k');  %%LIU:由起始点开始按照正下，左下，正左，起始点的顺序围成一个正方形（矩形），并对其填充黄色。因此，只有黄色方块右上角点为实际的起始点。
% % % hold on;
% % % end

% % % device = [14 15 17 19;2 5 13 12];
size_device = size(device,1);
a=[14 15;17 19]; %%LIU:障碍物的左下角点和右上角点
for i = 1:size_device
fill([device(i, 3),device(i, 3),device(i, 1),device(i, 1)],...
     [device(i, 4),device(i, 2),device(i, 2),device(i, 4)],'k');  %%%LIU:按照设备的右上，右下，左下，左上角点的顺序围成一个正方形（矩形），并对其填充黑色
 %%LIU:由起始点开始按照正下，左下，正左，起始点的顺序围成一个正方形（矩形），并对其填充黄色。因此，只有黄色方块右上角点为实际的起始点。
hold on;
end

b=[20 14;20 13;20 12;20 11;20 10;20 9;20 8;20 7;20 6]; %%已有给定线缆绘制
plot(b(:,1),b(:,2),'b-','LineWidth',3);

fill([real(1, 1)-0.4,real(1, 1)+0.4,real(1, 1)+0.4,real(1, 1)-0.4],...
     [real(1, 2)+0.4,real(1, 2)+0.4,real(1, 2)-0.4,real(1, 2)-0.4],'y');
hold on;
fill([real(3, 1)-0.4,real(3, 1)+0.4,real(3, 1)+0.4,real(3, 1)-0.4],...
     [real(3, 2)+0.4,real(3, 2)+0.4,real(3, 2)-0.4,real(3, 2)-0.4],'g');
hold on;

ps=[xStart,yStart;real(1,1),real(1,2)];
pt=[xTarget,yTarget;real(3,1),real(3,2)];
plot(ps(:,1),ps(:,2),'m-','LineWidth',1);
plot(pt(:,1),pt(:,2),'m-','LineWidth',1);

% % % ps=[];
% % % for i=1:1+lead_node_num-1
% % %     ps=[ps;map(i,1),map(i,2)];
% % % end
% % % ps=[ps;real(1,1),real(1,2)];
% % % % % % plot(ps(1:size(ps,1),1),ps(1:size(ps,1),2),'g-','LineWidth',3);
% % % 
% % % pt=[];
% % % for i=size(map,1)-lead_node_num+1:size(map,1)
% % %     pt=[pt;map(i,1),map(i,2)];
% % % end
% % % pt=[pt;real(3,1),real(3,2)];
% % % % % % plot(pt(1:size(pt,1),1),pt(1:size(pt,1),2),'g-','LineWidth',3);
% % %  
% % % 
% % % scatter(ps(:,1),ps(:,2),'b');  %%LIU:绘制散点图，scatter(x,y,sz,c)函数：指定圆颜色。要以相同的颜色绘制所有圆圈，请将 c 指定为颜色名称或 RGB 三元数。要使用不同的颜色，请将 c 指定为向量或由 RGB 三元数组成的三列矩阵。
% % % plot(ps(:,1),ps(:,2),'m-','LineWidth',1);
% % % scatter(pt(:,1),pt(:,2),'b');
% % % plot(pt(:,1),pt(:,2),'m-','LineWidth',1);
% % % hold on;

% if (~isempty(path))  %%LIU:~isempty(A) 表示如果A是空元素（空元素表示未赋值的元素，0并不是空元素），结果为0（false）；否则结果为1（true）。
%     plot(path(:,1),path(:,2),'m-','LineWidth',1);  %%plot：绘制二维线图，m代表颜色为洋红，-代表线型为实线，LineWidth 4 代表线宽为4。
% end
%  plot(map(1:1+lead_node_num-1,1),map(1:1+lead_node_num-1,2),'g-','LineWidth',3);real(1,1),
%  plot(map(size(map,1)-lead_node_num+1:size(map,1),1),map(size(map,1)-lead_node_num+1:size(map,1),2),'g-','LineWidth',3);
%  plot(map(2:2+lead_node_num,1),map(2:2+lead_node_num,2),'g-','LineWidth',3);
 
end




 