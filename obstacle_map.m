% % % function map = obstacle_map(xStart,yStart,xTarget,yTarget,MAX_X,MAX_Y)
% % % %This function returns a map contains random distribution obstacles.
% % % map =[5 2;5 5;5 6;5 7;5 8;5 9;5 10;5 18;6 18;7 18;8 18;9 18;10 18;10 17;10 16;7 2;2 3;11 20;1 11;20 16;20 20];
% % % %  [5 2;5 10;10 2;20 20];[5 2;5 5;5 6;5 7;5 8;5 9;5 10;5 18;6 18;7 18;8 18;9 18;10 18;10 17;10 16;7 2;2 3;11 20;1 11;20 16;20 17;20 20];
% % % % [5 2;5 3;6 2;5 5;8 5]; 
% % % %5 5;5 6;5 7;5 8;5 9;5 10;5 18;6 18;7 18;8 18;9 18;10 18;10 17;10 16;7 2; 11 20;11 19;5 11;5 12;5 13;5 14;5 15;5 16;50 50;50 48;50 47;50 46;50 45;50 44;50 43;2 17
% % % end


function map = obstacle_map(device,connect_NODE_set,wang_length,MAX_X,MAX_Y)
%% LIU:预埋设备所占的空间点 矩形左下到右上循环
map=[];
% % % device = [14 15 17 19;2 5 13 12];
size_device = size(device,1);
for i = 1:size_device
x_left_bottom = device(i,1);
y_left_bottom = device(i,2);
x_right_top = device(i,3);
y_right_top = device(i,4);
x = x_left_bottom ; y = y_left_bottom;
obstacle_device = [];
while x <= x_right_top
    while y <= y_right_top
        deviceNode = [x y];
        obstacle_device = [obstacle_device;deviceNode];
        y = y + 1;
    end
    x = x + 1;
    y = y_left_bottom;
end
map=[map ; obstacle_device];
end
%%%0821被注释
% % % %% LIU:将所有实际起止点间的路径设为障碍物  将所有连接点对以矩阵的形式调用
% % % 
% % % 
% % % size_set = size(connect_NODE_set,1) ;
% % % for k=1:size_set
% % %     xStart = connect_NODE_set(k,1); yStart = connect_NODE_set(k,2);lead_direction_Start = connect_NODE_set(k,3);
% % %     xTarget = connect_NODE_set(k,4);yTarget = connect_NODE_set(k,5);lead_direction_Target = connect_NODE_set(k,6);
% % %     lead_length=connect_NODE_set(k,7);R= connect_NODE_set(k,8);
% % %     
% % %     
% % %     Node_Start = [xStart yStart];
% % %     Node_Target = [xTarget yTarget];
% % %     lead_node_num = ceil(lead_length/wang_length);
% % %     R_node_num = ceil(R/wang_length); %%%0821修改加入了最小弯折半径作为起始必须有的长度
% % %     lead_path_Start = [];
% % %     for i=1:(lead_node_num+R_node_num)
% % %         switch lead_direction_Start
% % %             case  1
% % %                 passby_Start(i,1) = xStart;  passby_Start(i,2) = yStart + i;
% % %             case  2
% % %                 passby_Start(i,1) = xStart + i;  passby_Start(i,2) = yStart;
% % %             case  3
% % %                 passby_Start(i,1) = xStart;  passby_Start(i,2) = yStart - i;
% % %             case  4
% % %                 passby_Start(i,1) = xStart - i;  passby_Start(i,2) = yStart;
% % %         end
% % %         passNode_Start = [passby_Start(i,1) passby_Start(i,2)];
% % %         lead_path_Start = [lead_path_Start; passNode_Start]; %%%0821修改后lead_path实际上已经包含了最小弯折的要求
% % %     end
% % %     
% % %     lead_path_Target = [];
% % %     for i=(lead_node_num+R_node_num):-1:1
% % %         switch lead_direction_Target
% % %             case  1
% % %                 passby_Target(i,1) = xTarget;  passby_Target(i,2) = yTarget + i;
% % %             case  2
% % %                 passby_Target(i,1) = xTarget + i;  passby_Target(i,2) = yTarget;
% % %             case  3
% % %                 passby_Target(i,1) = xTarget;  passby_Target(i,2) = yTarget - i;
% % %             case  4
% % %                 passby_Target(i,1) = xTarget - i;  passby_Target(i,2) = yTarget;
% % %         end
% % %         passNode_Target = [passby_Target(i,1) passby_Target(i,2)];
% % %         lead_path_Target = [lead_path_Target; passNode_Target];
% % %     end
% % % 
% % %     obstacle_lead=[Node_Start; lead_path_Start; lead_path_Target ; Node_Target];
% % %     map=[map ; obstacle_lead];
% % % end
end























%%0715被注释
% % % function map = obstacle_map(xStart,yStart,xTarget,yTarget,lead_length,wang_length,lead_direction_Start,lead_direction_Target,MAX_X,MAX_Y)
% % % %This function returns a map contains random distribution obstacles.
% % % 
% % % map = [];
% % % 
% % % obstacle = [14 15;14 16;14 17;14 18;14 19;15 15;15 16;15 17;15 18;15 19;16 15;16 16;16 17;16 18;16 19;17 15;17 16;17 17;17 18;17 19;...
% % %     20 14;20 13;20 12;20 11;20 10;20 9;20 8;20 7;20 6];
% % % %%%将引出线的点均设为障碍点
% % % 
% % % Node_Start = [xStart yStart];
% % % Node_Target = [xTarget yTarget];
% % % 
% % % % % %     map(1,1) = xStart;
% % % % % %     map(1,2) = yStart;
% % % % % % 
% % % % % %     k=2; 
% % % % % % 
% % % % % %     
% % % % % %     map(k,1) = xTarget;
% % % % % %     map(k,2) = yTarget;  %%LIU:map表中的第一行始终记录起始点横纵坐标；最后一行始终记录目标点的横纵坐标。
% % %     
% % %     
% % %     lead_node_num = ceil(lead_length/wang_length);
% % %     lead_path_Start = [];
% % %     for i=1:lead_node_num-1
% % %         switch lead_direction_Start
% % %             case  1
% % %                 passby_Start(i,1) = xStart;  passby_Start(i,2) = yStart + i;
% % %             case  2
% % %                 passby_Start(i,1) = xStart + i;  passby_Start(i,2) = yStart;
% % %             case  3
% % %                 passby_Start(i,1) = xStart;  passby_Start(i,2) = yStart - i;
% % %             case  4
% % %                 passby_Start(i,1) = xStart - i;  passby_Start(i,2) = yStart - i;
% % %         end
% % %         passNode_Start = [passby_Start(i,1) passby_Start(i,2)];
% % %         lead_path_Start = [lead_path_Start; passNode_Start];
% % %     end
% % %     
% % %      lead_path_Target = [];
% % %     for i=(lead_node_num-1):-1:1
% % %         switch lead_direction_Target
% % %             case  1
% % %                 passby_Target(i,1) = xTarget;  passby_Target(i,2) = yTarget + i;
% % %             case  2
% % %                 passby_Target(i,1) = xTarget + i;  passby_Target(i,2) = yTarget;
% % %             case  3
% % %                 passby_Target(i,1) = xTarget;  passby_Target(i,2) = yTarget - i;
% % %             case  4
% % %                 passby_Target(i,1) = xTarget - i;  passby_Target(i,2) = yTarget - i;
% % %         end
% % %         passNode_Target = [passby_Target(i,1) passby_Target(i,2)];
% % %         lead_path_Target = [lead_path_Target; passNode_Target];
% % %     end
% % %     
% % %     map=[Node_Start; lead_path_Start; obstacle; lead_path_Target ; Node_Target];
% % % 
% % % end

















% % % function map = obstacle_map(xStart,yStart,xTarget,yTarget,MAX_X,MAX_Y,wang_length,lead_length,lead_direction_Start,lead_direction_Target)
% % % %This function returns a map contains random distribution obstacles.
% % % 
% % % map = [];
% % % lead_node_num = ceil(lead_length/wang_length);
% % % 
% % %     map(2,1) = xStart;
% % %     map(2,2) = yStart;
% % % switch lead_direction_Start
% % %     case  1
% % %         xStart = xStart;  yStart = yStart+lead_node_num;  
% % %     case  2
% % %         xStart = xStart+lead_node_num;  yStart = yStart;
% % %     case  3
% % %         xStart = xStart;  yStart = yStart-lead_node_num;
% % %     case  4
% % %         xStart = xStart-lead_node_num;  yStart = yStart;
% % % end
% % %     map(1,1) = xStart;
% % %     map(1,2) = yStart;
% % % 
% % %     k=3; 
% % % 
% % %     
% % %     map(k,1) = xTarget;
% % %     map(k,2) = yTarget;  %%LIU:map表中的第一行始终记录起始点横纵坐标；最后一行始终记录目标点的横纵坐标。
% % %     switch lead_direction_Target
% % %         case  1
% % %             xTarget = xTarget;  yTarget = yTarget+lead_node_num;
% % %         case  2
% % %             xTarget = xTarget+lead_node_num;  yTarget = yTarget;
% % %         case  3
% % %             xTarget = xTarget;  yTarget = yTarget-lead_node_num;
% % %         case  4
% % %             xTarget = xTarget-lead_node_num;  yTarget = yTarget;
% % %     end
% % %     map(k+1,1) = xTarget;
% % %     map(k+1,2) = yTarget;
% % % end















% %     rand_map = rand(MAX_X,MAX_Y);   %%LIU:rand函数产生由在(0, 1)之间均匀分布的随机数组成的数组。此处将产生MAX_X行、MAX_Y列在区间（0，1）的随机矩阵
% %     map = [];
% %     map(1,1) = xStart;
% %     map(1,2) = yStart;
% %     k=2;
% %     obstacle_ratio = 0.1;  
% %     for i = 1:1:MAX_X
% %         for j = 1:1:MAX_Y
% %             if( (rand_map(i,j) < obstacle_ratio) && (i~= xStart || j~=yStart) && (i~= xTarget || j~=yTarget))  %%LIU:小于障碍率的随机数对应的位置且不是起始点和目标点，将其设为障碍点，且将该点横纵坐标按行记录在map表中
% %                 map(k,1) = i;
% %                 map(k,2) = j;
% %                 k=k+1;
% %             end    
% %         end
% %     end
% %     map(k,1) = xTarget;
% %     map(k,2) = yTarget;  %%LIU:map表中的第一行始终记录起始点横纵坐标；最后一行始终记录目标点的横纵坐标。
% % end
 