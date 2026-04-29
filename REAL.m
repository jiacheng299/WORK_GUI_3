function real = REAL(lead_length,R,wang_length,lead_direction_Start,xStart,yStart,lead_direction_Target,xTarget,yTarget)

real = [];

lead_node_num = ceil(lead_length/wang_length);
R_node_num = ceil(R/wang_length);
switch lead_direction_Start
    case  1
        xStart_Real = xStart;  yStart_Real = yStart+lead_node_num+R_node_num;  father_of_xStart_Real = xStart_Real;  father_of_yStart_Real = yStart_Real-1; xStart_lead = xStart;  yStart_lead = yStart+lead_node_num;
    case  2
        xStart_Real = xStart+lead_node_num+R_node_num;  yStart_Real = yStart;  father_of_xStart_Real = xStart_Real-1;  father_of_yStart_Real = yStart_Real; xStart_lead = xStart+lead_node_num;  yStart_lead = yStart;
    case  3
        xStart_Real = xStart;  yStart_Real = yStart-lead_node_num-R_node_num;  father_of_xStart_Real = xStart_Real;  father_of_yStart_Real = yStart_Real+1; xStart_lead = xStart;  yStart_lead = yStart-lead_node_num;
    case  4
        xStart_Real = xStart-lead_node_num-R_node_num;  yStart_Real = yStart;  father_of_xStart_Real = xStart_Real+1;  father_of_yStart_Real = yStart_Real; xStart_lead = xStart-lead_node_num;  yStart_lead = yStart;
end
real(1,1)= xStart_Real;
real(1,2)= yStart_Real;
real(2,1)=father_of_xStart_Real;
real(2,2)=father_of_yStart_Real;
real(5,1)=xStart_lead;
real(5,2)=yStart_lead;


switch lead_direction_Target
        case  1
            xTarget_Real = xTarget;  yTarget_Real = yTarget+lead_node_num+R_node_num;  child_of_xTarget_Real = xTarget_Real;  child_of_yTarget_Real = yTarget_Real-1; xTarget_lead = xTarget;  yTarget_lead = yTarget+lead_node_num;
        case  2
            xTarget_Real = xTarget+lead_node_num+R_node_num;  yTarget_Real = yTarget;  child_of_xTarget_Real = xTarget_Real-1;  child_of_yTarget_Real = yTarget_Real; xTarget_lead = xTarget+lead_node_num;  yTarget_lead = yTarget;
        case  3
            xTarget_Real = xTarget;  yTarget_Real = yTarget-lead_node_num-R_node_num;  child_of_xTarget_Real = xTarget_Real;  child_of_yTarget_Real = yTarget_Real+1; xTarget_lead = xTarget;  yTarget_lead = yTarget-lead_node_num;
        case  4
            xTarget_Real = xTarget-lead_node_num-R_node_num;  yTarget_Real = yTarget;  child_of_xTarget_Real = xTarget_Real+1;  child_of_yTarget_Real = yTarget_Real; xTarget_lead = xTarget-lead_node_num;  yTarget_lead = yTarget;
end
real(3,1)= xTarget_Real;
real(3,2)= yTarget_Real;
real(4,1)=child_of_xTarget_Real;
real(4,2)=child_of_yTarget_Real;
real(6,1)=xTarget_lead;
real(6,2)=yTarget_lead;

end