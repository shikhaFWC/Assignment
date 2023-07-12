module helloworldfpga(input W,X,Y,Z,output A,B,C,D,cl);
reg W=0,X=0,Y=0,Z=0 ;
reg[28:0] delay;
wire clk;
reg mclk;
qlal4s3b_cell_macro u_qlal4s3b_cell_macro (
        .Sys_Clk0 (clk),
    );
always @(posedge clk) begin
	delay=delay+1;
  if (delay>40000000) begin
     mclk=!mclk;
     delay=0;
  end
end
always @(negedge mclk) begin
  A=((!Z)&&Y&&X&&W)||(Z&&!Y)||(Z&&(!X))||(Z&&(!W));
  B=((!Y)&&X&&W)||(Y&&(!X))||(Y&&(!W));
  C=((!X)&&W)||(X&&(!W));
  D=(!W);
end
assign cl=mclk;
endmodule
