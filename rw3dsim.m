  numberofsteps=100;
  numberofwalks=10000;
  time = 0 : numberofsteps;
  meansqdisplacement = zeros(numberofsteps+1,1);
  meandisplacement= zeros(numberofsteps+1,1);
  mean1displacement= zeros(numberofsteps+1,1);
  meansq1displacement= zeros(numberofsteps+1,1);

  for walk = 1 : numberofwalks

    x = zeros(numberofsteps+1,1);
    y = zeros(numberofsteps+1,1);
    z = zeros(numberofsteps+1,1);
  
   for step = 2 : numberofsteps + 1

      updateposition = [ x(step-1) + 1.0, y(step-1),       z(step-1); 
                      x(step-1) - 1.0, y(step-1),       z(step-1); 
                      x(step-1),       y(step-1) + 1.0, z(step-1); 
                      x(step-1),       y(step-1) - 1.0, z(step-1); 
                      x(step-1),       y(step-1),       z(step-1) + 1.0; 
                      x(step-1),       y(step-1),       z(step-1) - 1.0
                      x(step-1) + 1.0, y(step-1) + 1.0, z(step-1) + 1.0
                      x(step-1) + 1.0, y(step-1) + 1.0, z(step-1) - 1.0
                      x(step-1) + 1.0, y(step-1) - 1.0, z(step-1) + 1.0
                      x(step-1) + 1.0, y(step-1) - 1.0, z(step-1) - 1.0
                      x(step-1) - 1.0, y(step-1) + 1.0, z(step-1) + 1.0
                      x(step-1) - 1.0, y(step-1) + 1.0, z(step-1) - 1.0
                      x(step-1) - 1.0, y(step-1) - 1.0, z(step-1) + 1.0
                      x(step-1) - 1.0, y(step-1) - 1.0, z(step-1) - 1.0];

      k = ceil ( 14.0 * rand );

      x(step) = updateposition(k,1);
      y(step) = updateposition(k,2);
      z(step) = updateposition(k,3);

      sqdisplacement = x(step)^2 + y(step)^2 + z(step)^2;
      meansqdisplacement(step) = meansqdisplacement(step) + sqdisplacement;
      displacement =  x(step) + y(step) + z(step);
      meandisplacement(step) = meandisplacement(step) + displacement;
      d1displacement = x(step);
      mean1displacement(step) = mean1displacement(step) + d1displacement;
      sq1displacement = x(step)^2;
      meansq1displacement(step) = meansq1displacement(step) + sq1displacement;
 
   end

  end

  meansqdisplacement(:,1) = meansqdisplacement(:,1) / numberofwalks;
  meandisplacement(:,1) = meandisplacement(:,1) / numberofwalks;
  meansq1displacement(:,1) = meansq1displacement(:,1) / numberofwalks;
  mean1displacement(:,1) = mean1displacement(:,1) / numberofwalks;
  plot (time,meandisplacement,'LineWidth', 1 );

  xlabel ( 'Time' )
  ylabel ( 'Mean square displacement' )
  title ( ' 3D Random Walk ' )

  return
 
  
