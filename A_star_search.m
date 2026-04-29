function path = A_star_search(map,real,multi_already,MAX_X,MAX_Y,R,back_num)
%%

big_number = 500 ; %%%LIU:一个大数，尽量往大就对了，至少得大于MAX_X,MAX_Y，后面会用到，在判断终点前路径会将路径代价与之比较，并可能赋给某参数，该大数需要为全场最大。
%This part is about map/obstacle/and other settings
%     R=3;  %%%LIU:最小弯折半径
%     wang_length = 1; %%%LIU:最小网格边长
%     back_num = ceil(R/wang_length);%%%当前父节点回溯点个数，向上取整

    %pre-process the grid map, add offset
    size_map = size(map,1);  %%LIU:得到障碍点（包含起始点和终点）的行数（在此例也等于列数），为了后面循环所有障碍点赋值
    Y_offset = 0;
    X_offset = 0;
    
    
    
    %Define the 2D grid map array.
    %Obstacle=-1, Target = 0, Start=1，Multi_already = -2
    MAP=2*(ones(MAX_X,MAX_Y));  %%LIU:创建所有元素为2的矩阵，整个地图中的网格均赋值为2，为了后面以-1，0，1赋值障碍点，目标点和起始点来区分可行路径点（即后续路径点网格值为2）
    
    %Initialize MAP with location of the obstacle
    %%%LIU:需要先将所有障碍点赋值为-1（此步在赋实际起止点之前），因为所有起止和实际搜索起止点都在障碍物列表里面，这里赋为-1后，对于每次调用本搜索函数，下面的对实际起止点赋值为1和0的代码会覆盖掉该点的-1值，避免当次搜索起止点变为障碍物，找不到终点
    for i = 1: size_map  %%LIU：此循环范围代表除去第一个起始位和最后一个目标位 %%%将名义起点也包含在障碍物内
        xval=floor(map(i, 1)) + X_offset;
        yval=floor(map(i, 2)) + Y_offset;
        MAP(xval,yval)=-1;
    end
    
   %Initialize MAP with location of the target
    xval=floor(real(3, 1)) + X_offset;  %%LIU:floor函数：朝负无穷大方向取整(向下取整)  %%LIU:为什么要取整？？ 
    yval=floor(real(3, 2)) + Y_offset;
    xTarget=xval;
    yTarget=yval;
    TARGET = [xTarget,yTarget];
    MAP(xval,yval)=0;    
    
% % %         %Initialize MAP with location of the obstacle
% % %     for i = 2: size_map-1  %%LIU：此循环范围代表除去第一个起始位和最后一个目标位
% % %         xval=floor(map(i, 1)) + X_offset;
% % %         yval=floor(map(i, 2)) + Y_offset;
% % %         MAP(xval,yval)=-1;
% % %     end 
    
    %Initialize MAP with location of the start point
    xval=floor(real(1, 1)) + X_offset;
    yval=floor(real(1, 2)) + Y_offset;
    xStart=xval;
    yStart=yval;
    START = [xStart,yStart];
    MAP(xval,yval)=1;
    
% % %     %Initialize MAP with location of the obstacle
% % %     for i = 1: size_map  %%LIU：此循环范围代表除去第一个起始位和最后一个目标位 %%%将名义起点也包含在障碍物内
% % %         xval=floor(map(i, 1)) + X_offset;
% % %         yval=floor(map(i, 2)) + Y_offset;
% % %         MAP(xval,yval)=-1;
% % %     end
    
% % %     Initialize MAP with 初始化多分支已探索线缆
size_multi_already = size(multi_already,1) ;   
for i = 1:size_multi_already
     xval=floor(multi_already(i, 1));
     yval=floor(multi_already(i, 2));
     MAP(xval,yval)=-2;
end
     
    
    
% %     %Initialize MAP with location of the target
% %     xval=floor(map(size_map, 1)) + X_offset;  %%LIU:floor函数：朝负无穷大方向取整(向下取整)  %%LIU:为什么要取整？？ 
% %     yval=floor(map(size_map, 2)) + Y_offset;
% %     xTarget=xval;
% %     yTarget=yval;
% %     TARGET = [xTarget,yTarget];
% %     MAP(xval,yval)=0;
    
% %     %Initialize MAP with location of the obstacle
% %     for i = 2: size_map-1  %%LIU：此循环范围代表除去第一个起始位和最后一个目标位
% %         xval=floor(map(i, 1)) + X_offset;
% %         yval=floor(map(i, 2)) + Y_offset;
% %         MAP(xval,yval)=-1;
% %     end 
% %     
% %     %Initialize MAP with location of the start point
% %     xval=floor(map(1, 1)) + X_offset;
% %     yval=floor(map(1, 2)) + Y_offset;
% %     xStart=xval;
% %     yStart=yval;
% %     START = [xStart,yStart];
% %     MAP(xval,yval)=1;
 
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %LISTS USED FOR ALGORITHM
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    % 定义节点的数据结构
    %--------------------------------------------------------------------------
    %%%LIU:Node |X val |Y val |Parent X val |Parent Y val |h(n) |g(n)|f(n)|Child wan num|Parent X equ |Parent Y equ |Child come direction |Parent come direction |caodao_cost |
    %--------------------------------------------------------------------------
    Node = zeros(1,13); %%%
    % OPEN LIST STRUCTURE
    %--------------------------------------------------------------------------
    %%%LIU: |X val |Y val |Parent X val |Parent Y val |h(n) |g(n)|f(n)|Child wan num|Parent X equ |Parent Y equ |Child come direction |Parent come direction |caodao_cost |
    %--------------------------------------------------------------------------
% % %     
    OPEN=repmat(Node,(2*MAX_X)*(2*MAX_Y),1);  %%LIU:repmat（A,m,n）函数：其实后面两个数字代表了m行n列个子空间，把A的内容放到每个子空间内
    OPEN_COUNT=0;  %%LIU:目的是节点表计数
    % CLOSED LIST STRUCTURE
    %--------------------------------------------------------------------------
    %%%LIU: |X val |Y val |Parent X val |Parent Y val |h(n) |g(n)|f(n)|Child wan num|Parent X equ |Parent Y equ |Child come direction |Parent come direction |caodao_cost |
    %--------------------------------------------------------------------------
    CLOSED=repmat(Node,(2*MAX_X)*(2*MAX_Y),1);
    CLOSED_COUNT=0;
    % 设置启发函数的距离计算公式，DISTANCE_FLAG=0：曼哈顿距离，DISTANCE_FLAG=1：欧式距离
    DISTANCE_FLAG = 1;
    % 初始化父节点
    xChildNode=xStart;
    yChildNode=yStart;
    xFatherNode=real(2,1);
    yFatherNode=real(2,2);
% % %     xFatherNode=xStart;
% % %     yFatherNode=yStart;
    caodao_coefficient = 1; %%%LIU:初始化槽道系数
    caodao_cost = 0;
    num_wan=0;%%%
    num_Child_wan=0; %%%
    zhewan_cost=0.5 * num_wan;%%%
    goal_cost= DISTANCE(xFatherNode,yFatherNode,xTarget,yTarget,DISTANCE_FLAG); %%LIU:初始化的h()值
    path_cost=0;                                                                %%LIU:初始化的g()值
    total_cost = goal_cost+path_cost+zhewan_cost+caodao_cost ;
    xFatherNodeEqual=0;  %%%
    yFatherNodeEqual=0;  %%%LIU:相同父节点值
    Child_come_direction=0; %%%LIU:初始化父到子的方向
    Father_come_direction=0; %%%LIU:初始化爷到父的方向
    Node_Father = [xChildNode,yChildNode,xFatherNode,yFatherNode,goal_cost,path_cost,total_cost,num_Child_wan,xFatherNodeEqual,yFatherNodeEqual,Child_come_direction,Father_come_direction,caodao_cost];%%%
    % 将父节点加入CLOSED中
    CLOSED_COUNT=CLOSED_COUNT+1;
    CLOSED(CLOSED_COUNT,:)= Node_Father;
%%
%This part is your homework
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% START ALGORITHM
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    fig_num = 1;
    while(1) %you have to dicide the Conditions for while loop exit 
     
        %
        %finish the while loop
        %
        % 获取当前父节点坐标
        xFatherNode = Node_Father(1); yFatherNode = Node_Father(2);FatherDirection = Node_Father(11);
        %%%LIU:获取当前父节点实际弯折数
        %%%LIU:获取当前父节点的父节点（爷节点）
        num_Father_wan = Node_Father(8); %%%LIU:一般当前父节点的实际弯折数，就等于记录的弯折数
        
        is_father_last_node = 0;
        if (abs(xFatherNode-xTarget)+abs(yFatherNode-yTarget)==1) %%%LIU:特殊情况：当前父节点为目标节点相邻点的情况，需要判断爷节点是否处于目标节点对角线来判断实际弯折数是否还等于记录的弯折数
            for i = 1:CLOSED_COUNT % 寻找当前节点的父节点
                if xFatherNode == CLOSED(i,1) && yFatherNode == CLOSED(i,2) && FatherDirection == CLOSED(i,11) %%LIU:节点存储时，第一列为子节点横坐标，第二列为子节点纵坐标。找到该点作为子节点时的数据结构
                    xGrandNode = CLOSED(i,3);  %%LIU:节点存储时，第3列为父节点横坐标，第四列为节点纵坐标。上一行找到对应的数据结构，即可由三、四列得出父节点坐标
                    yGrandNode = CLOSED(i,4);
                    GrandDirection = CLOSED(i,12);
                    break;  %%LIU:跳出for循环，即停止搜索当前该节点父节点，因为已找到
                end
            end %%%
            %%LIU:for循环结尾
            if (abs(xGrandNode-xTarget))*(abs(yGrandNode-yTarget))==1
                is_father_last_node = 1;
            end
        end


        
        
        %%%LIU:初始化当前父节点可弯折性
        is_can_wan = 1; %%%LIU:1代表可弯，0代表不可弯
        % 初始化子节点List
        Node_Child_List = repmat(Node,4,1);
        % 查找当前父节点的所有子节点（初次循环的父节点为起始点）  %%LIU:按照从正上方节点开始顺时针搜寻，每45度
% % % 
        if xFatherNode ~= xTarget || yFatherNode < yTarget  
        Node_Child_List(1,1) = xFatherNode;   Node_Child_List(1,2) = yFatherNode+1;  Node_Child_List(1,11) = 1;
        end
        %%Node_Child_List(2,1) = xFatherNode+1; Node_Child_List(2,2) = yFatherNode+1;
        if xFatherNode < xTarget || yFatherNode ~= yTarget
        Node_Child_List(2,1) = xFatherNode+1; Node_Child_List(2,2) = yFatherNode;  Node_Child_List(2,11) = 2;
        end
        %%Node_Child_List(4,1) = xFatherNode+1; Node_Child_List(4,2) = yFatherNode-1;
        if xFatherNode ~= xTarget || yFatherNode > yTarget  
        Node_Child_List(3,1) = xFatherNode;   Node_Child_List(3,2) = yFatherNode-1;  Node_Child_List(3,11) = 1;
        end
        %%Node_Child_List(6,1) = xFatherNode-1; Node_Child_List(6,2) = yFatherNode-1;
        if xFatherNode > xTarget || yFatherNode ~= yTarget
        Node_Child_List(4,1) = xFatherNode-1; Node_Child_List(4,2) = yFatherNode;  Node_Child_List(4,11) = 2;
        end
    
        PositionX = xFatherNode;%%%
        PositionY = yFatherNode;%%%LIU:初始化得在循环开始之前
        Direction = FatherDirection;
        for k=1:back_num %%%
            for i = 1:CLOSED_COUNT % 寻找当前节点的父节点
                if PositionX == CLOSED(i,1) && PositionY == CLOSED(i,2) && Direction == CLOSED(i,11)  %%LIU:节点存储时，第一列为子节点横坐标，第二列为子节点纵坐标。找到该点作为子节点时的数据结构
                        PositionX = CLOSED(i,3);  %%LIU:节点存储时，第3列为父节点横坐标，第四列为节点纵坐标。上一行找到对应的数据结构，即可由三、四列得出父节点坐标
                        PositionY = CLOSED(i,4);
                        Direction = CLOSED(i,12);
                        num_wan = CLOSED(i,8); %%% 找到到当前点最短路径的父节点弯折数
                    break;  %%LIU:跳出for循环，即停止搜索当前该节点父节点，因为已找到
                end %%%
            end  %%LIU:开始准备下一个点（即上一个点找到的父节点）的父节点搜寻准备
            
% % %             %%%0821
% % %             if  PositionX == real(2,1) &&  PositionY == real(2,2)
% % %                 is_can_wan = 0;
% % %                 break;
% % %             end
% % %             %%%0821
           
            
% % %             if num_wan ~= num_Father_wan %%%
% % %                 is_can_wan = 0; %%%
% % %                 break; %%%LIU：跳出回溯循环
% % %             end

            if is_father_last_node
                if num_wan ~= num_Father_wan && num_wan ~= num_Father_wan-1
                    is_can_wan = 0; %%%
                    break; %%%LIU：跳出回溯循环
                end
            elseif num_wan ~= num_Father_wan %%%
                is_can_wan = 0; %%%
                break; %%%LIU：跳出回溯循环
            end
            
           

%%%%%%以下是没有加起始节点父节点前需要进行的判断，未加之前第一步探索沿各个方向都没有弯折，都等于起始节点弯折数0；加了之后第一步探索沿引出线的弯折是0，垂直于引出线的弯折加了1。注：通过和爷节点（起始节点的父节点）判断，未加之前爷节点还初始化为起始节点。  
%%%%%%若规定引出线长小于最小弯折半径，只需修改 k<back_num 中 k小于的再小一点
% % %             if PositionX == xStart && PositionY == yStart && k < back_num %%% back_num是指上一拐点之后的一个点，因此，搜索到起点时，即时搜索了back_num次也不行，小于更不行
% % %                 is_can_wan = 0; %%%LIU:如果探索次数较少，即（回溯至起点，且发现回溯点不够），则跳出回溯循环，并且不可弯 
% % %                 break;  %%LIU:跳出回溯循环
% % %             end %%%
        end %%%
            
        for i=1:4
            % 当前子节点坐标
            xChildNode = Node_Child_List(i,1);
            yChildNode = Node_Child_List(i,2);
            ChildDirection = Node_Child_List(i,11);
            % 如果子节点超出地图范围，则不满足要求
            if(xChildNode<1 || xChildNode>MAX_X || yChildNode<1 || yChildNode>MAX_Y)
               continue;  %%LIU:continue：代表满足上述条件（即超出边界）则不往下进行，回到for循环开始下一个点判断
            end
            % 如果子节点位于障碍物中，则不满足要求
            if(MAP(xChildNode,yChildNode)==-1)
                continue;
            end
% % %       % 如果子节点在CLOSED中，则不满足要求
            CHILD_IS_IN_CLOSED = 0;
            for j=1:CLOSED_COUNT
                if(CLOSED(j,1)==xChildNode && CLOSED(j,2)==yChildNode && CLOSED(j,11)==ChildDirection)
                    CHILD_IS_IN_CLOSED = 1;
                    break;
                end
            end
            if (CHILD_IS_IN_CLOSED == 1)
                continue;
            end
             %%%LIU: 如果父节点处不能弯，但当前子节点已发生弯折,则不满足要求，跳过当前点，继续下一个点判断。
            is_wan = zhewan(xChildNode,yChildNode,xFatherNode,yFatherNode,CLOSED(CLOSED_COUNT,3),CLOSED(CLOSED_COUNT,4),CLOSED(CLOSED_COUNT,9),CLOSED(CLOSED_COUNT,10),xTarget,yTarget,CLOSED_COUNT+1); %%%LIU:当前子节点是否弯折,0代表未完折，其余（1或2）代表弯折
            if (is_can_wan == 0 && is_wan ~= 0) %%%LIU: 如果父节点处不能弯，但当前子节点已发生弯折,则不满足要求，跳过当前点，继续下一个点判断。
                continue;
            end
            
            %%% LIU:判断是否
            caodao_coefficient = 1; 
            if(MAP(xChildNode,yChildNode)==-2)  %%%LIU:若子节点在多分支已探索节点里，如果父节点也在，说明沿着槽道在走（还未分叉），则降低槽道系数，如果父节点不在，而子节点在，说明交叉，这时候就按照障碍处理，直接跳过当前子节点
                if (MAP(xFatherNode,yFatherNode)==-2)
                caodao_coefficient = 0;
                else 
                    continue; %%%0808:如果不想使其只局限于开始时不分叉才能走的槽道，将continue换为caodao_coefficient = 1;这样即使不沿槽道，在这个点也能走，如果沿着槽道又能减小代价。
                end
            end
            
            
            
            
            % 计算满足要求的子节点信息
            num_Father_wan = CLOSED(CLOSED_COUNT,8);  %%%LIU:当前父节点弯折数
% % %             is_wan = zhewan(xChildNode,yChildNode,xFatherNode,yFatherNode,CLOSED(CLOSED_COUNT,3),CLOSED(CLOSED_COUNT,4),CLOSED(CLOSED_COUNT,9),CLOSED(CLOSED_COUNT,10),xTarget,yTarget,CLOSED_COUNT); %%%LIU:当前子节点是否弯折,0代表未完折，其余（1或2）代表弯折
            num_Child_wan = num_Father_wan + is_wan; %%%
            zhewan_cost = 0.5 * num_Child_wan; %%%
            %%%zhewan_cost=zhewan(xChildNode,yChildNode,xFatherNode,yFatherNode,CLOSED(CLOSED_COUNT,3),CLOSED(CLOSED_COUNT,4),xTarget,yTarget,CLOSED_COUNT);
            goal_cost=DISTANCE(xChildNode,yChildNode,xTarget,yTarget,0);  %%%LIU:h()使用曼哈顿距离
            %%goal_cost=distance(xChildNode,yChildNode,xTarget,yTarget);  %%LIU:这里使用的是小写版的distance,代表h（）使用的是欧氏距离
            path_cost = Node_Father(6) + DISTANCE(xFatherNode,yFatherNode,xChildNode,yChildNode,0);
            %%%path_cost = CLOSED(CLOSED_COUNT,6) + DISTANCE(xFatherNode,yFatherNode,xChildNode,yChildNode,0);
            caodao_cost = Node_Father(13) + caodao_coefficient * DISTANCE(xFatherNode,yFatherNode,xChildNode,yChildNode,0);
            %%path_cost = DISTANCE(xFatherNode,yFatherNode,xChildNode,yChildNode,DISTANCE_FLAG)    %%LIU:这里使用大写DISTANCE,但参数中DISTANCE_FLAG取值为1，代表使用的是欧氏距离，这里为计算子节点到父节点的欧氏距离
            total_cost = path_cost+goal_cost+zhewan_cost+caodao_cost;  %%LIU:代表f()=g()+h()
            Node_Child_List(i,3) = xFatherNode;  %%LIU:之前定义Node_Child_List为（1*7）矩阵，第一列为子节点横坐标，第二列为子节点纵坐标，第三列为父节点横坐标，第四列为父节点纵坐标，第五列为距离终点代价h(),第六列为已走过的路径代价g(),第七列为总代价f().
            Node_Child_List(i,4) = yFatherNode;
            Node_Child_List(i,5) = goal_cost;
            Node_Child_List(i,6) = path_cost;
            Node_Child_List(i,7) = total_cost;
            Node_Child_List(i,8) = num_Child_wan; %%%
            Node_Child_List(i,12) = FatherDirection; %%%
            Node_Child_List(i,13) = caodao_cost; %%%
            % 判断当前节点是否在OPEN中
            CHILDE_IS_IN_OPEN_FLAG = 0;
            INDEX_CHILD_IN_OPEN = 0;
            for j=1:OPEN_COUNT
                if(OPEN(j,1)==xChildNode && OPEN(j,2)==yChildNode && OPEN(j,11)==ChildDirection)
                    CHILDE_IS_IN_OPEN_FLAG = 1;
                    INDEX_CHILD_IN_OPEN = j;
                    break;
                end
            end
            % 如果不在OPEN中则加入，如果在OPEN中则判断当前路径total_cost是否比之前的小，
            % 如果更小，则更新之前节点在OPEN中的信息
            if (CHILDE_IS_IN_OPEN_FLAG)
                if (total_cost<OPEN(INDEX_CHILD_IN_OPEN,7))
                    OPEN(INDEX_CHILD_IN_OPEN,3) = xFatherNode;
                    OPEN(INDEX_CHILD_IN_OPEN,4) = yFatherNode;
                    OPEN(INDEX_CHILD_IN_OPEN,6) = path_cost;
                    OPEN(INDEX_CHILD_IN_OPEN,7) = total_cost;
                    OPEN(INDEX_CHILD_IN_OPEN,8) = num_Child_wan; %%%
                    OPEN(INDEX_CHILD_IN_OPEN,12) = FatherDirection;
                    OPEN(INDEX_CHILD_IN_OPEN,13) = caodao_cost;
                elseif(total_cost==OPEN(INDEX_CHILD_IN_OPEN,7)) %%%LIU:如果相等的情况
                    OPEN(INDEX_CHILD_IN_OPEN,9) = xFatherNode; %%%
                    OPEN(INDEX_CHILD_IN_OPEN,10) = yFatherNode; %%%
                    OPEN(INDEX_CHILD_IN_OPEN,6) = path_cost; %%%
                    OPEN(INDEX_CHILD_IN_OPEN,7) = total_cost; %%%
                    OPEN(INDEX_CHILD_IN_OPEN,8) = num_Child_wan; %%%
                    OPEN(INDEX_CHILD_IN_OPEN,12) = FatherDirection;
                    OPEN(INDEX_CHILD_IN_OPEN,13) = caodao_cost;
                end
            else
                OPEN_COUNT = OPEN_COUNT+1;
                OPEN(OPEN_COUNT,1) = xChildNode;
                OPEN(OPEN_COUNT,2) = yChildNode;
                OPEN(OPEN_COUNT,3) = xFatherNode;
                OPEN(OPEN_COUNT,4) = yFatherNode;
                OPEN(OPEN_COUNT,5) = goal_cost;
                OPEN(OPEN_COUNT,6) = path_cost;
                OPEN(OPEN_COUNT,7) = total_cost;
                OPEN(OPEN_COUNT,8) = num_Child_wan;
                OPEN(OPEN_COUNT,11) = ChildDirection;
                OPEN(OPEN_COUNT,12) = FatherDirection;
                OPEN(OPEN_COUNT,13) = caodao_cost;
            end
        end
 
        TARGET_IS_IN_OPEN_FLAG = 0;
        
        for j=1:OPEN_COUNT
            if(OPEN(j,1)==xTarget && OPEN(j,2)==yTarget && OPEN(j,7)<big_number )
                a = 1; %%%a代表目标节点是否能弯折，初始化为可以弯折
                b=2;
                child_of_xTarget = real(4,1); child_of_yTarget = real(4,2); %%%LIU:用于判断折弯的子节点改为目标节点下一点（在引出线上）
                num_Target_wan = OPEN(j,8); %%%LIU:目标节点弯折数
                num_child_of_Target_wan = num_Target_wan + zhewan(child_of_xTarget,child_of_yTarget,OPEN(j,1),OPEN(j,2),OPEN(j,3),OPEN(j,4),0,0,xTarget,yTarget,CLOSED_COUNT+1); %%%LIU:目标节点弯折数

                PositionX_Target = OPEN(j,3);%%% LIU:因为当前目标节点还未加入CLOSED，因此不能将目标节点加入下方循环，但可以根据OPEN表得出目标节点的父节点，使其加入下方循环
                PositionY_Target= OPEN(j,4);%%%LIU:初始化得在循环开始之前
                Direction_Target = OPEN(j,12);
                results=repmat(Node,back_num,1); %%%LIU:results数组只记录回溯的节点，不记录自身，即开始回溯的节点，因此，back_num-1
% % %                 results=repmat(Node,back_num-1,1); %%%LIU:results数组只记录回溯的节点，不记录自身，即开始回溯的节点，因此，back_num-1
                results_count=0;
                     
                
                for k=1:back_num-1 %%%LIU:因为第一个点是将目标节点父节点作为子节点搜索，因此，num_wan直接就是目标节点父节点的弯折数，因此back_num-1。%%%LIU:注：数据结构中num_wan指子节点的弯折数
                    for i = 1:CLOSED_COUNT % 寻找当前节点的父节点
                        if PositionX_Target == CLOSED(i,1) && PositionY_Target == CLOSED(i,2) && Direction_Target == CLOSED(i,11)  %%LIU:节点存储时，第一列为子节点横坐标，第二列为子节点纵坐标。找到该点作为子节点时的数据结构
                            PositionX_Target = CLOSED(i,3);  %%LIU:节点存储时，第3列为父节点横坐标，第四列为节点纵坐标。上一行找到对应的数据结构，即可由三、四列得出父节点坐标
                            PositionY_Target = CLOSED(i,4);
                            Direction_Target = CLOSED(i,12);
                            num_wan = CLOSED(i,8); %%% 找到到当前点弯折数
                            k;
                            results_count=results_count+1;
                            results(results_count,:) = CLOSED(i,:); %%%LIU:将路径点从CLOSED表存至results中(若可以弯折返给CLOSED,若不可弯折，返给OPEN表)，并在CLOSED中删除
                            CLOSED(i,:) = CLOSED(CLOSED_COUNT+1,:); %%%LIU:CLOSED_COUNT+1行是零行，即将该行赋零达到删除目的
% % %                             CLOSED_COUNT = CLOSED_COUNT-1;
                            b = 10;
                            break;  %%LIU:跳出for循环，即停止搜索当前该节点父节点，因为已找到
                        end %%%
                    end  %%LIU:开始准备下一个点（即上一个点找到的父节点）的父节点搜寻准备
                    results;
                    
                    num_wan;
                    if num_child_of_Target_wan == num_Target_wan  %%%LIU:该判断是在引出线长大于最小弯折半径的前提下，若目标节点父节点在引出线上（即目标节点子节点弯折数相比目标节点不会增加，代表目标点处未发生弯折）（通过和目标节点子节点判断是否弯折，即判断目标点处是否发生弯折），则不用再往前回溯，一定满足弯折半径；否则再通过回溯判断。  %%%LIU:若引出线长小于最小弯折半径，则if后改为当回溯循环次数k=某个值时跳出循环（即减少回溯次数），然后加上end.同时将下面的else if 换为 if。（相当于目标点没有折弯的话，加了一个判断停止回溯条件，即回溯次数，不影响另一个回溯停止条件，即当前回溯点的折弯判断）
                        break;
                    elseif num_wan ~= num_Target_wan %%%LIU:如果判断发生弯折，将判断路径中的所有子节点全部从CLOSED表中（借由results数组）移至OPEN表，并将总代价赋予极大值（防止接下来open代价最小再原路探索，只有延长路径后再次出现在OPEN中再使用新路径），目标节点也需要赋予极大值（不在closed中）
                        OPEN(j,7)=big_number; %%%LIU:目标节点总代价赋予极大值
                        for i=1:results_count-1 %%%LIU:只有目标节点到弯折点之间的点需要回归OPEN，并被赋予大值（不包括弯折点，因为弯折点是由垂直于回溯方向来的，不影响后面重新沿回溯方向走到弯折点，前后不属于同一个点），所以需要减个1，并且后面需要将弯折点还回closed表
                        OPEN_COUNT = OPEN_COUNT+1 ;
                        OPEN(OPEN_COUNT,:)= results(i,:);
                        OPEN(OPEN_COUNT,7)=big_number; %%%LIU:路径节点总代价赋予极大值
                        end
                        
                        CLOSED_COUNT = CLOSED_COUNT+1 ;
                        CLOSED(CLOSED_COUNT,:)= results(results_count,:);  %%%LIU：将弯折点还回CLOSED表（不需要将弯折点加入OPEN和赋大值）
% % %                         
% %                         results_count = results_count+1;
                        another_Direction = -results(results_count,11)+3; %%%LIU:将方向值，若1转换为2，若2转换为1
                        for i = 1:CLOSED_COUNT % 寻找当前弯折点沿着回溯方向的父节点（即不发生弯折的父节点，前提是存在，这种情况在多分支槽道代价为0时可能会出现）
                            if results(results_count,1) == CLOSED(i,1) && results(results_count,2) == CLOSED(i,2) && another_Direction == CLOSED(i,11)  %%LIU:节点存储时，第一列为子节点横坐标，第二列为子节点纵坐标。找到该点作为子节点时的数据结构
                                results_count=results_count+1;
                                results(results_count,:) = CLOSED(i,:); %%%LIU:将弯折点沿着回溯方向的父节点加入results
                                CLOSED(i,:) = CLOSED(CLOSED_COUNT+1,:); %%%LIU:CLOSED_COUNT+1行是零行，即将该行赋零达到删除目的
                                OPEN_COUNT = OPEN_COUNT+1 ;
                                OPEN(OPEN_COUNT,:)= results(results_count,:) %%% 将弯折点沿回溯方向的父节点加入OPEN表
                            end
                        end
                        
% % %                         
                        a=0 %%%LIU:目标节点不能弯折
                        break; %%%LIU：跳出回溯循环
                    end
                end %%%
                
                if a == 1 %%%LIU:若判断可以弯折，则将results存的路径点又还回CLOSED表
                    TARGET_IS_IN_OPEN_FLAG=1;
                    for i=1:results_count
                        CLOSED_COUNT = CLOSED_COUNT+1 ;
                        CLOSED(CLOSED_COUNT,:)= results(i,:);  
                    end
                    % 将目标节点放入CLOSED中
                    CLOSED_COUNT = CLOSED_COUNT+1;
                    CLOSED(CLOSED_COUNT,:) = OPEN(j,:);  %%LIU:将目标点7个数据一整行放入CLOSED节点表新建的最后一行
                end
                
            end
        end
        
        % 如果找到目标节点，则终止while循环
        if (TARGET_IS_IN_OPEN_FLAG==1)
            break;
        end
        % 判断OPEN是否为空，OPEN为空则代表没找到路径
        IS_OPEN_EMPTY_FLAG = false;
        if OPEN_COUNT == 0
            IS_OPEN_EMPTY_FLAG = true;
        end
        if IS_OPEN_EMPTY_FLAG
            break;
        end
        % 如果没找到目标节点，找出当前代价最小的节点
        temp_cost=OPEN(1,7);
        INDEX_MINCOST_IN_OPEN = 1;
        for j=2:OPEN_COUNT
            if (temp_cost>OPEN(j,7))
                temp_cost = OPEN(j,7);
                INDEX_MINCOST_IN_OPEN = j;
            end
        end
        % 将其作为父节点
        Node_Father = OPEN(INDEX_MINCOST_IN_OPEN,:);
        % 将其加入CLOSED
        CLOSED_COUNT = CLOSED_COUNT+1;
        CLOSED(CLOSED_COUNT,:) = OPEN(INDEX_MINCOST_IN_OPEN,:);
        % 将其弹出OPEN，并更新OPEN  %%LIU:即将最小代价点整行从OPEN表中删除，即下方单元格向上移一格
        for j=INDEX_MINCOST_IN_OPEN:OPEN_COUNT
            OPEN(j,:) = OPEN(j+1,:);  %%LIU:类似于表格中下方单元格向上移一格
        end
        OPEN_COUNT = OPEN_COUNT-1;  %%LIU:OPEN表计数减一
        
        
        % 可视化搜索列表OPEN和CLOSED
% %         visualize_LIST( CLOSED,CLOSED_COUNT,OPEN,OPEN_COUNT,START,TARGET );  %%使用了定义的visualize_LIST函数，在visualize_LIST.m文件
% %         pause(0.1);  %%LIU:每次搜索的间隔时间  %%此行以下可认为是导出GIF的标准代码
% %         F=getframe(gcf); %%LIU:F=getframe(gcf)：捕获图窗窗口的内部区域，不包括菜单和工具栏。
% %         I=frame2im(F);  %%LIU:frame2im(F)：从单个影片帧 F 返回索引图像数据 X 和关联的颜色图 map。
% %         [I,map]=rgb2ind(I,256);
% %         if (fig_num==1)
% %             imwrite(I,map,'test.gif','gif','Loopcount',inf,'DelayTime',0.2);  %%LIU:imwrite将 GIF 文件写入当前文件夹。名称-值对组 'LoopCount',Inf 使动画连续循环。'DelayTime',1 在每个动画图像显示之间指定了一秒的时滞。
% %         else
% %             imwrite(I,map,'test.gif','gif','WriteMode','append','DelayTime',0.2);  %%LIU:将多个图像保存到一个 GIF 文件中。因为 GIF 文件不支持三维数据，所以应调用rgb2ind，使用颜色图map将图像中的 RGB 数据转换为索引图像A。要将多个图像添加到第一个图像中，请使用名称-值对组参数 'WriteMode','append' 调用 imwrite。
% %         end
% %         fig_num = fig_num+1; %%此行及以上可认为是导出GIF的标准代码
    end %End of While Loop
    OPEN;
        CLOSED;
% % %         xGrandNode
% % %         yGrandNode
        OPEN_COUNT;
        CLOSED_COUNT;
    
    %Once algorithm has run The optimal path is generated by starting of at the
    %last node(if it is the target node) and then identifying its parent node
    %until it reaches the start node.This is the optimal path  %%LIU:一旦算法运行，通过在最后一个节点（如果它是目标节点）开始生成最优路径，然后识别其父节点，直到它到达起始节点。这是最佳路径
    
    %
    %How to get the optimal path after A_star search?
    %please finish it
    %
    %% 循环完成后处理结果
    if TARGET_IS_IN_OPEN_FLAG %OpenList中如果出现目标点则代表搜索完成找到路径,根据CloseList中的数据画出图像
        PositionX = xTarget;
        PositionY = yTarget;
        Direction = CLOSED(CLOSED_COUNT,11);
        PATH = [xTarget yTarget];
        SunNodeX=0; %%% 
        SunNodeY=0; %%% 孙节点坐标
        while 1        
            for i = 1:CLOSED_COUNT % 寻找当前节点的父节点
                if PositionX == CLOSED(i,1) && PositionY == CLOSED(i,2) && Direction == CLOSED(i,11) %%LIU:节点存储时，第一列为子节点横坐标，第二列为子节点纵坐标。找到该点作为子节点时的数据结构
                    PositionX = CLOSED(i,3);  %%LIU:节点存储时，第3列为父节点横坐标，第四列为节点纵坐标。上一行找到对应的数据结构，即可由三、四列得出父节点坐标
                    PositionY = CLOSED(i,4);  
                    Direction = CLOSED(i,12);
% % %                     if (CLOSED(i,9) ~= 0 && ((SunNodeX-CLOSED(i,9))*(SunNodeY-CLOSED(i,10)) == 0)) %%%LIU:父节点相同情况
% % %                         SunNodeX = PositionX; %%%
% % %                         SunNodeY = PositionY; %%%
% % %                         PositionX = CLOSED(i,9); %%%
% % %                         PositionY = CLOSED(i,10); %%%
% % %                     else SunNodeX = PositionX; %%%
% % %                          SunNodeY = PositionY; %%%
% % %                          PositionX = CLOSED(i,3);  %%LIU:节点存储时，第3列为父节点横坐标，第四列为节点纵坐标。上一行找到对应的数据结构，即可由三、四列得出父节点坐标
% % %                          PositionY = CLOSED(i,4);  
% % %                     end
% %                     PositionX = CLOSED(i,3);  %%LIU:节点存储时，第3列为父节点横坐标，第四列为节点纵坐标。上一行找到对应的数据结构，即可由三、四列得出父节点坐标
% %                     PositionY = CLOSED(i,4);      
                    Pos = [PositionX PositionY];
                    PATH = [PATH;Pos];  %%LIU:不断插入新的父节点（从尾到头的路径点），按行插入
                    break;  %%LIU:跳出for循环，即停止搜索当前该节点父节点，因为已找到
                end
            end  %%LIU:开始准备下一个点（即上一个点找到的父节点）的父节点搜寻准备     
            if PositionX == xStart && PositionY == yStart
                break;  %%LIU:跳出while循环，即停止寻找任何点的父节点，因为已到起点
            end
        end
    elseif IS_OPEN_EMPTY_FLAG %OpenList为空则代表没找到路径
        msgbox('未搜索到路径！');
    end
    
   path = PATH;
end
 
% 启发函数的距离计算，可根据flag选择欧氏距离或是曼哈顿距离
function d = DISTANCE(xTarget,yTarget,xGoal,yGoal,flag)
    % flag==0：曼哈顿距离，flag==1：欧氏距离
    if (flag==0)
        d = abs(xTarget-xGoal)+abs(yTarget-yGoal);
    elseif(flag==1)
        d = distance(xTarget,yTarget,xGoal,yGoal);
    end
end
% 欧式距离计算
function dist = distance(x1,y1,x2,y2)
%This function calculates the distance between any two cartesian 
%coordinates.
%   Copyright 2009-2010 The MathWorks, Inc.
dist=sqrt((x1-x2)^2 + (y1-y2)^2);
end

%%
%%%LIU
function IS_WAN=zhewan(xChildNode,yChildNode,xFatherNode,yFatherNode,xGrandNode,yGrandNode,xGrandNodeEqu,yGrandNodeEqu,xTarget,yTarget,yitansuo)
IS_WAN=0;
    if ((yitansuo>1 && (xChildNode-xGrandNode)*(yChildNode-yGrandNode) ~= 0 && (xChildNode-xGrandNodeEqu)*(yChildNode-yGrandNodeEqu) ~= 0))   %%LIU:通过判断子节点和爷节点是否处于斜对角线位置来判断是否折弯，同时考虑到等代价爷节点（爷到父）是否也折弯，同时成立则孙节点（当前子节点）的折弯数量加1（弯折代价加0.5）。%%%LIU:也可改成另一种判断方式，思路：其实，仔细考虑，只要当前父节点存在等效爷节点，两个爷节点必然处于对角位置，那么当前子节点一定会和其中一个爷节点处于同一直线上，也就是说弯折数量一定不会加1。那么，只要判断实际爷节点不在一条线且等效爷节点坐标为0（即不存在等效爷节点）即可判断弯折。
        IS_WAN = IS_WAN + 1;
    end
    if(((abs(xFatherNode-xTarget))*(abs(yFatherNode-yTarget))==1) && (abs(xChildNode-xTarget)+abs(yChildNode-yTarget)==1)) %%LIU:这里的数值1均建立在边长为1的正方形网格下
        IS_WAN = IS_WAN + 1;   %%LIU:对于子节点与目标节点弯折相邻的特殊节点，一旦将该子节点作为父节点探索，他的子节点将会有目标节点，目标节点一旦出现在OPEN表中，直接循环结束，而不是去比较是否有其他在终点前不弯折而更短的路径（差距也就是是否多此一弯），但的确在到此步之前也是最小代价节点，属于正常探索。上面的式子可以判断在某个节点的待确定子节点是否会发生弯折，从而加上弯折代价，可能就不走该子节点，但对于待确定子节点出现了目标节点，则无论是否弯折，都将直接结束探索；因此，引出本式，可以考虑在目标节点的爷节点若是处于对角线位置（即前面所说的特殊父节点），针对接下来为特殊子节点（即目标节点的父节点）的特殊节点，将本应在目标节点加入OPEN表后才加的弯折代价，提前一步加到特殊子节点（即这种情况下目标节点的父节点）上（反正如果真走到这一节点，接下来也不可能走其他路径）
    %%%LIU:修改这里的加1时，记得同步修改前面判断特殊情况弯折半径处的减1
    end
end