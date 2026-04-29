% Used for Motion Planning for Mobile Robots
% Thanks to HKUST ELEC 5660 
close all; clear all; clc;

fprintf('====================================\n');
fprintf('多功能模块数字孪生可视化软件 - MATLAB路径规划模块\n');
fprintf('====================================\n');

% 创建图形窗口
fig = figure;
set(fig, 'Renderer', 'painters');
set(fig, 'Position', [500, 50, 900, 700]);  % 增加宽度以显示时间信息
hold on;

%% 记录总开始时间
total_start_time = tic;

%%YUXIN:输入端
MAX_X = 100;%%蜂窝夹层板的长
MAX_Y = 100; %%蜂窝夹层板的宽
wang_length = 10; %%%电缆线组件的宽

fprintf('开始加载输入文件...\n');
load_start_time = tic;
device = load('device.txt');%%障碍物（矩形电连接器/蜂窝打孔）的左下角横坐标|左下角纵坐标|右上角横坐标|右上角纵坐标，%%通过（矩形电连接器/蜂窝打孔）中心位置坐标、安装方向和长宽转化可得
connect_NODE_set = load('connectFile.txt');%%连接器I中心点横坐标|连接器I中心点纵坐标|连接器I出线方向|连接器II中心点横坐标|连接器II中心点纵坐标|连接器II出线方向|最小引出段直线段长|最小弯折半径|
load_time = toc(load_start_time);
fprintf('文件加载完成，耗时: %.2f 秒\n', load_time);
%%YUXIN:输入端结束

% 在图形上显示基本信息
text(MAX_X*0.02, MAX_Y*1.02, sprintf('路径规划结果图'), ...
    'FontSize', 10, 'FontWeight', 'bold');

multi_already = [];

fprintf('开始创建障碍物地图...\n');
map_start_time = tic;
map = obstacle_map(device,connect_NODE_set,wang_length,MAX_X,MAX_Y);
map_time = toc(map_start_time);
fprintf('障碍物地图创建完成，耗时: %.2f 秒\n', map_time);

% Environment map in 2D space 

size_set = size(connect_NODE_set,1);
fprintf('====================================\n');
fprintf('共有 %d 条路径需要规划\n', size_set);
fprintf('====================================\n');

PATHS = cell(1,size_set);%%1103建立合适大小的空元胞数组 

%% 记录每条路径的规划时间
path_planning_times = zeros(size_set, 1);

% 创建一个进度文本区域
progress_text = annotation('textbox', [0.02, 0.02, 0.3, 0.1], ...
    'String', sprintf('准备开始路径规划...\n总路径数: %d', size_set), ...
    'FontSize', 9, 'BackgroundColor', [0.95 0.95 0.95], ...
    'EdgeColor', 'black', 'LineWidth', 1);

for k = 1:size_set
    fprintf('\n--- 正在规划第 %d/%d 条路径 ---\n', k, size_set);
    % 更新进度显示
    set(progress_text, 'String', sprintf('正在规划路径 %d/%d\n已耗时: %.1f秒', ...
        k, size_set, toc(total_start_time)));
    
    xStart = connect_NODE_set(k,1);
    yStart = connect_NODE_set(k,2);
    xTarget = connect_NODE_set(k,4);
    yTarget = connect_NODE_set(k,5);
    
    lead_length = connect_NODE_set(k,7);
    lead_direction_Start = connect_NODE_set(k,3);
    lead_direction_Target = connect_NODE_set(k,6);
    
    R = connect_NODE_set(k,8);  %%%LIU:最小弯折半径。在A_star_search中
    back_num = ceil(R/wang_length);%%%当前父节点回溯点个数，向上取整（自身作为回溯的第一个点判断）
    lead_node_num = ceil(lead_length/wang_length);
    
    real = REAL(lead_length,R,wang_length,lead_direction_Start,xStart,yStart,lead_direction_Target,xTarget,yTarget);
    
    % 可视化当前路径
    fprintf('  可视化地图...\n');
    visualize_map(map,xStart,yStart,xTarget,yTarget, MAX_X, MAX_Y,lead_node_num,real,device);
    
    % 在图上显示当前路径信息
    text(xStart, yStart+2, sprintf('起点%d', k), ...
        'FontSize', 8, 'Color', 'red', 'FontWeight', 'bold');
    text(xTarget, yTarget+2, sprintf('终点%d', k), ...
        'FontSize', 8, 'Color', 'green', 'FontWeight', 'bold');
    
    % Waypoint Generator Using the A*
    fprintf('  开始A*路径搜索...\n');
    path_start_time = tic;
    path = A_star_search(map,real,multi_already,MAX_X,MAX_Y,R,back_num);
    path_time = toc(path_start_time);
    path_planning_times(k) = path_time;
    fprintf('  路径搜索完成，耗时: %.2f 秒\n', path_time);
    
    %optimal path
    for path_cnt = 2:size(path,1)-1
        scatter(path(path_cnt,1),path(path_cnt,2),'b');  %%LIU:绘制散点图
        hold on;
    end
    
    if (~isempty(path))  %%LIU:~isempty(A) 表示如果A是空元素
        % 绘制路径
        h_path = plot(path(:,1),path(:,2),'m-','LineWidth',2);  %%plot：绘制二维线图
        
        % 在路径中间添加编号
        if size(path,1) > 3
            mid_idx = floor(size(path,1)/2);
            text(path(mid_idx,1), path(mid_idx,2), sprintf('P%d', k), ...
                'FontSize', 9, 'Color', 'magenta', 'BackgroundColor', 'white', ...
                'HorizontalAlignment', 'center');
        end
        
        PATHS{k} = path;%%1103每条线缆的所有路径存储到里面
        fprintf('  找到有效路径，路径点数量: %d\n', size(path,1));
    else
        fprintf('  警告: 未找到有效路径!\n');
        % 在图上显示警告
        text((xStart+xTarget)/2, (yStart+yTarget)/2, sprintf('路径%d失败', k), ...
            'FontSize', 10, 'Color', 'red', 'FontWeight', 'bold', ...
            'BackgroundColor', 'yellow', 'HorizontalAlignment', 'center');
    end
    
    % 实时更新进度
    drawnow;
end

%% 计算总运行时间
total_time = toc(total_start_time);

%%YUXIN:输出端将PATHS元胞数组中拐点找出保留，可通过判断进行。
% 打开文件用于写入 guaidian.txt
fileID1 = fopen('guaidian.txt', 'w');

% 打开文件用于写入扩展拐点的文件 guaidian_extended.txt
fileID2 = fopen('guaidian_extended.txt', 'w');

% 遍历每条路径
for k = 1:length(PATHS)
    path = PATHS{k};
    
    R = connect_NODE_set(k,8)/2;
    % 如果路径为空，则跳过
    if isempty(path)
        continue;
    end
    
    % 初始化拐点数组，包含起点
    guaidian = path(1, :);
    
    % 初始化扩展后的拐点数组
    guaidian_extended = path(1, :); % 起点直接加入
    
    % 遍历路径中的点，找到拐点
    for i = 2:size(path, 1)-1
        % 当前点与前后点
        prev_point = path(i-1, :);
        curr_point = path(i, :);
        next_point = path(i+1, :);
        
        % 判断方向变化，通过斜率变化检测拐点
        prev_direction = atan2(curr_point(2) - prev_point(2), curr_point(1) - prev_point(1));
        next_direction = atan2(next_point(2) - curr_point(2), next_point(1) - curr_point(1));
        
        % 如果方向有明显变化，则当前点是拐点
        if abs(prev_direction - next_direction) > 1e-3  % 方向变化的阈值
            guaidian = [guaidian; curr_point];
            
            % 计算扩展的三个点，先把两个单位向量求出来，这样后面只要操作单位向量
            unit_prev = (prev_point - curr_point) / norm(curr_point - prev_point);
            unit_next = (next_point - curr_point) / norm(next_point - curr_point);
            
            % 第一个点：拐点向上一点方向移动 R
            p1 = curr_point + R * unit_prev;
            
            % 第二个点：拐点向上一点方向移动 (1 - √2/2)R，向下一点方向移动 (1 - √2/2)R
            offset = (1 - sqrt(2) / 2) * R;
            p2 = curr_point + offset * unit_prev + offset * unit_next;
            
            % 第三个点：拐点向下一点方向移动 R
            p3 = curr_point + R * unit_next;
            
            % 加入扩展后的拐点数组
            guaidian_extended = [guaidian_extended; p1; p2; p3];
        end
    end
    
    % 将终点也作为拐点
    guaidian = [guaidian; path(end, :)];
    guaidian_extended = [guaidian_extended; path(end, :)]; % 终点直接加入
    
    % 将拐点信息写入 guaidian.txt
    fprintf(fileID1, '%d:\n', k);
    fprintf(fileID1, '%.2f,%.2f\n', guaidian');
    fprintf(fileID1, '\n');
    
    % 将扩展拐点信息写入 guaidian_extended.txt
    fprintf(fileID2, '%d:\n', k);
    fprintf(fileID2, '%.2f,%.2f\n', guaidian_extended');
    fprintf(fileID2, '\n');
end

% 关闭文件
fclose(fileID1);
fclose(fileID2);

%% 在图形上添加时间信息统计框
time_info_box = annotation('textbox', [0.65, 0.02, 0.33, 0.15], ...
    'String', sprintf(['运行时间统计:\n' ...
                       '总运行时间: %.2f 秒\n' ...
                       '文件加载: %.2f 秒\n' ...
                       '地图创建: %.2f 秒\n' ...
                       '路径搜索: %.2f 秒\n' ...
                       '总路径数: %d\n' ...
                       '完成时间: %s'], ...
                      total_time, load_time, map_time, sum(path_planning_times), ...
                      size_set, datestr(now, 'HH:MM:SS')), ...
    'FontSize', 9, 'BackgroundColor', [0.9 0.95 0.9], ...
    'EdgeColor', 'green', 'LineWidth', 2, 'FontWeight', 'bold');

%% 添加性能统计
performance_box = annotation('textbox', [0.65, 0.18, 0.33, 0.08], ...
    'String', sprintf('性能统计:\n平均每路径: %.2f 秒\n最快路径: %.2f 秒\n最慢路径: %.2f 秒', ...
                      mean(path_planning_times), min(path_planning_times), ...
                      max(path_planning_times)), ...
    'FontSize', 9, 'BackgroundColor', [0.95 0.95 0.9], ...
    'EdgeColor', 'blue', 'LineWidth', 1);

%% 添加图例和说明
legend_items = {};


if ~isempty(legend_items)
    legend(legend_items, 'Location', 'northeast', 'FontSize', 9);
end

% 添加标题和轴标签
title(sprintf('多功能模块路径规划结果 (总时间: %.1f秒)', total_time), ...
    'FontSize', 14, 'FontWeight', 'bold');
xlabel('X坐标', 'FontSize', 11);
ylabel('Y坐标', 'FontSize', 11);
grid on;

% 设置坐标轴范围
axis([0 MAX_X 0 MAX_Y]);
axis equal;

% 更新进度框为完成状态
set(progress_text, 'String', sprintf('路径规划完成!\n总时间: %.1f秒\n完成时间: %s', ...
    total_time, datestr(now, 'HH:MM:SS')), ...
    'BackgroundColor', [0.9 1.0 0.9]);

%% 保存结果图
try
    print(fig, 'path_planning_result.png', '-dpng', '-r300');
    fprintf('\n结果图已保存为: path_planning_result.png\n');
catch
    fprintf('\n警告: 无法保存结果图\n');
end

%% 生成简化的总结报告到文件
fileID3 = fopen('runtime_summary.txt', 'w');
fprintf(fileID3, '多功能模块数字孪生可视化软件 - 运行时间报告\n');
fprintf(fileID3, '==========================================\n');
fprintf(fileID3, '生成时间: %s\n', datestr(now, 'yyyy-mm-dd HH:MM:SS'));
fprintf(fileID3, '总路径数: %d\n', size_set);
fprintf(fileID3, '总运行时间: %.2f 秒\n', total_time);
fprintf(fileID3, '平均每路径: %.2f 秒\n', total_time/size_set);
fprintf(fileID3, '\n时间明细:\n');
fprintf(fileID3, '  文件加载: %.2f 秒\n', load_time);
fprintf(fileID3, '  地图创建: %.2f 秒\n', map_time);
fprintf(fileID3, '  路径搜索: %.2f 秒\n', sum(path_planning_times));
fprintf(fileID3, '\n各路径规划时间:\n');
for k = 1:size_set
    fprintf(fileID3, '  路径 %d: %.2f 秒\n', k, path_planning_times(k));
end
fclose(fileID3);

fprintf('\n====================================\n');
fprintf('所有计算完成！\n');
fprintf('结果文件已生成:\n');
fprintf('  - guaidian.txt\n');
fprintf('  - guaidian_extended.txt\n');
fprintf('  - runtime_summary.txt\n');
fprintf('  - path_planning_result.png\n');
fprintf('====================================\n');

figs = findobj('Type', 'figure');
if ~isempty(figs)
    fprintf('\n====================================\n');
    fprintf('图形窗口已打开！\n');
    fprintf('请查看生成的图片: path_planning_result.png\n');
    fprintf('关闭所有图形窗口后按 Enter 键退出\n');
    fprintf('====================================\n\n');
    
    % 等待所有图形窗口关闭
    for i = 1:length(figs)
        set(figs(i), 'CloseRequestFcn', 'closereq');
        waitfor(figs(i));
    end
end

% 最后等待用户确认
fprintf('\n按 Enter 键完全退出...\n');
