
set JOBS;
param TIME{JOBS};
set INCOMP, dimen 2;
param M := sum{i in JOBS} TIME[i];

var t_alfa;

minimize total_time: t_alfa;

var t{JOBS} >= 0;
var y{INCOMP}, binary;

subj to cons12{(a,b) in INCOMP}: t[a] >= t[b] + TIME[b] - y[a,b]*M;
subj to cons21{(a,b) in INCOMP}: t[b] >= t[a] + TIME[a] - (1 - y[a,b])*M;

subj to cons_alfa{i in JOBS}: t_alfa >= t[i] + TIME[i];

end;

