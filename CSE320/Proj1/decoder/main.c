/**
 * Main program for testing the decoder
 */
#include <stdio.h>
#include "decoder.h"

/*
 * Main
 */
int main()
{
  const char *encoded="\ 
    h^@aRah^Y^^lQe@Ral!ahahh*Q^^YeQaQQalal^!hahhQ!ePe*heal!P@hhQ\ 
    ^aa@lYh^eha^Plhl*YY*^^*alYlQ@@*^@le@PaPe^RQ!!^a@hahahh*Qa*^e\
    h^aPPe*ae!a@*aRalhl*Y!^ae*@PhahP@lhQ^^a@ahQQYhe^^*aY^!^laYQh\
    lahee@**l^YlPPlh@hYR*^^*YYhYaalQ^haY!@@hahPlYYRYYae*aR!ahYhe\
    ell*hallh@aaR^a^ae*@^*Y^!!*Qhl^hhlea^^hh^lQ*Plal*Y!Qah*Ya!Ya\
    ^h^eQQhhR*^ae^@P*aeaR**!a^@aPlhl^l^R*hY*eee@a^PahlP^lhRQQ@P^\
    ^Qa*Q!P@Y!a*a@alha@^ll^Yae^@hYR*^lhRh!!*e^h@Yh!eQh*hl^l^a^^Q\
    Q^haY!aQ*aPY!@^a^eaQlQ*a^a^^hYl^lh^aR^aQ^!h@haPe^l^YQah^@^hh\
    @lalhleYeQeP@R^l*ehee^haY*h^@lPl^a!!!QhlalaPQPP@PaR*ah^^*alh\
    hahhhlh^^!Y*e^PPh^YeQah!!ehY*h!a^@leh^eQh^*!Rh!YQ*eh^eQhlal!\
    hhl^YP^elaa^RQalQl^ae*!eQ*hhae!l*^Rh^h@Q*^^^@^P@hlhae!!^a@Re\
    ae^lh*QQa*^^e*!ehPh@QQPP@R*ahlQQ^hYaaPe^Rh^QPhhalhhYaahQYPe*\
    ^R*!*h!@haPYa^^h!Qh!*hal^h!YQ^a!aPeae^RYa@l@la!*Qa*eeah@haah\
    Qhl*aPaheeR*!!eQeP@le@lePe^@helh*Q^aahQa^YePhl^@ahhaR^l^!*ee\
    ^h!^^!*@YhaaP@@!Y!QY@hQehee@R^lh*h!@Q*Ph^^ah^^^ahl*!*halahaP\
    ahe^QPlh!*Qha*al^hahPl^aeae^RY!!Rh@aaP^PheeaQY@aPlQY@hh^ae*@\
    QQheQ^^alQe@@eYehaP^@Y!Y!*eh^a^^h*@haaP@R^l*Ph^^e*!^^!^l*Pla\
    YR^aQ^!h@haPe^l^YQah^@^hh\@lalhleYeQeP@R^l*ehee^haY*h^@lPl^a!!!QhlalaPQPP@PaR*ah^^*alh\
    hahhhlh^^!Y*e^PPh^YeQah!!ehY*h!a^@leh^eQh^*!Rh!YQ*eh^eQhlal!\
    hhl^YP^elaa^RQalQl^ae*!eQ*hhae!l*^Rh^h@Q*^^^@^P@hlhae!!^a@Re\
    ae^lh*QQa*^^e*!ehPh@QQPP@R*ahlQQ^hYaaPe^Rh^QPhhalhhYaahQYPe*\
    R*!*h!@haPYa^^h!Qh!*hal^h!YQ^a!aPeae^RYa@l@la!*Qa*eeah@haah\
    Qhl*aPaheeR*!!eQeP@le@lePe^@helh*Q^aahQa^YePhl^@ahhaR^l^!*ee\
    ^h!^^!*@YhaaP@@!Y!QY@hQehee@R^lh*h!@Q*Ph^^ah^^^ahl*!*halahaP\
    ahe^QPlh!*Qha*al^hahPl^aeae^RY!!Rh@aaP^PheeaQY@aPlQY@hh^ae*@\
    QQheQ^^alQe@@eYehaP^@Y!Y!*eh^a^^h*@haaP@R^l*Ph^^e*!^^!^l*Pla\
    YQ*hhl^Ylh@haahhlP^lh^!aPaR^l*eelPhhalYPe*^heYl@aQlPQPPe^ae^@P*aeaR**!a^@aPlhl^l^R*hY*eee@a^PahlP^lhRQQ@P^\
    ^Qa*Q!P@Y!a*a@alha@^ll^Yae^@hYR*^lhRh!!*e^h@Yh!eQh*hl^l^a^^Q\
                                                    Q^haY!aQ*aPY!@^a^eaQlQ*a^a^^hYl^lh^aR^aQ^!h@haPe^l^YQah^@^hh\
                                                        @lalhleYeQeP@R^l*ehee^haY*h^@lPl^a!!!QhlalaPQPP@PaR*ah^^*alh\
                                                            hahhhlh^^!Y*e^PPh^YeQah!!ehY*h!a^@leh^eQh^*!Rh!YQ*eh^eQhlal!\
                                                                hhl^YP^elaa^RQalQl^ae*!eQ*hhae!l*^Rh^h@Q*^^^@^P@hlhae!!^a@Re\
                                                                    ae^lh*QQa*^^e*!ehPh@QQPP@R*ahlQQ^hYaaPe^Rh^QPhhalhhYaahQYPe*\
                                                                        ^R*!*h!@haPYa^^h!Qh!*hal^h!YQ^a!aPeae^RYa@l@la!*Qa*eeah@haah\
                                                                            Qhl*aPaheeR*!!eQeP@le@lePe^@helh*Q^aahQa^YePhl^@ahhaR^l^!*ee\
                                                                                ^h!^^!*@YhaaP@@!Y!QY@hQehee@R^lh*h!@Q*Ph^^ah^^^ahl*!*halahaP\
                                                                                    ahe^QPlh!*Qha*al^hahPl^aeae^RY!!Rh@aaP^PheeaQY@aPlQY@hh^ae*@\
                                                                                        QQheQ^^alQe@@eYehaP^@Y!Y!*eh^a^^h*@haaP@R^l*Ph^^e*!^^!^l*Pla\
                                                                                            YR^aQ^!h@haPe^l^YQah^@^hh\
                                                                                                    @lalhleYeQeP@R^l*ehee^haY*h^@lPl^a!!!QhlalaPQPP@PaR*ah^^*alh\
                                                                                                                hahhhlh^^!Y*e^PPh^YeQah!!ehY*h!a^@leh^eQh^*!Rh!YQ*eh^eQhlal!\
                                                                                                                                hhl^YP^elaa^RQalQl^ae*!eQ*hhae!l*^Rh^h@Q*^^^@^P@hlhae!!^a@Re\
                                                                                                                                                    ae^lh*QQa*^^e*!ehPh@QQPP@R*ahlQQ^hYaaPe^Rh^QPhhalhhYaahQYPe*\
                                                                                                                                                                            ^R*!*h!@haPYa^^h!Qh!*hal^h!YQ^a!aPeae^RYa@l@la!*Qa*eeah@haah\
                                                                                                                                                                                                        Qhl*aPaheeR*!!eQeP@le@lePe^@helh*Q^aahQa^YePhl^@ahhaR^l^!*ee\
                                                                                                                                                                                                                                        ^h!^^!*@YhaaP@@!Y!QY@hQehee@R^lh*h!@Q*Ph^^ah^^^ahl*!*halahaP\
                                                                                                                                                                                                                                                                            ahe^QPlh!*Qha*al^hahPl^aeae^RY!!Rh@aaP^PheeaQY@aPlQY@hh^ae*@\
                                                                                                                                                                                                                                                                                                                    QQheQ^^alQe@@eYehaP^@Y!Y!*eh^a^^h*@haaP@R^l*Ph^^e*!^^!^l*Pla\
                                                                                                                                                                                                                                                                                                                                                                YQ*hhl^Ylh@haahhlP^lh^!aPaR^l*eelPhhalYPe*^heYl@aQlPQ*hhl^Ylh@haahhlP^lh^!aPaR^l*eelPhhalYPe*^heYl@aQlPQPPe";

  char decoded[1000];

  decoder(encoded, decoded, sizeof(decoded));
  printf("%s\n", decoded);

  return 0;
}

