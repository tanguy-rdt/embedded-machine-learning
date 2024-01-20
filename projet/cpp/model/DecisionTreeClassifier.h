#ifndef DECISION_TREE_CLASSIFIER_H
#define DECISION_TREE_CLASSIFIER_H

    // !!! This file is generated using emlearn !!!
#include <cstdint>

int32_t DecisionTreeClassifier_tree_roots[1] = { 0 };


static inline int32_t DecisionTreeClassifier_tree_0(const float *features, int32_t features_length) {
          if (features[324] < -0.341267f) {
              if (features[579] < -0.571154f) {
                  if (features[3] < -0.774373f) {
                      if (features[17] < -0.847406f) {
                          return 5;
                      } else {
                          if (features[464] < 0.026502f) {
                              return 1;
                          } else {
                              return 5;
                          }
                      }
                  } else {
                      if (features[502] < -0.247418f) {
                          if (features[966] < -0.617322f) {
                              if (features[848] < -0.636732f) {
                                  return 1;
                              } else {
                                  if (features[243] < -0.305125f) {
                                      return 8;
                                  } else {
                                      if (features[777] < -0.105863f) {
                                          return 0;
                                      } else {
                                          return 2;
                                      }
                                  }
                              }
                          } else {
                              return 5;
                          }
                      } else {
                          return 1;
                      }
                  }
              } else {
                  if (features[956] < -0.258645f) {
                      if (features[676] < -0.578308f) {
                          if (features[3] < -0.634289f) {
                              return 5;
                          } else {
                              if (features[996] < -0.461792f) {
                                  if (features[961] < 0.130789f) {
                                      return 9;
                                  } else {
                                      return 8;
                                  }
                              } else {
                                  return 2;
                              }
                          }
                      } else {
                          return 1;
                      }
                  } else {
                      if (features[79] < -0.501077f) {
                          if (features[646] < -0.475680f) {
                              return 2;
                          } else {
                              return 1;
                          }
                      } else {
                          return 0;
                      }
                  }
              }
          } else {
              if (features[251] < 0.262519f) {
                  if (features[1] < 0.748858f) {
                      if (features[423] < 0.212132f) {
                          if (features[5] < -0.439481f) {
                              if (features[511] < -0.397092f) {
                                  if (features[654] < -0.642903f) {
                                      if (features[93] < -0.582528f) {
                                          if (features[383] < -0.341860f) {
                                              if (features[970] < -0.692831f) {
                                                  return 8;
                                              } else {
                                                  return 2;
                                              }
                                          } else {
                                              if (features[1014] < -0.563255f) {
                                                  return 3;
                                              } else {
                                                  return 5;
                                              }
                                          }
                                      } else {
                                          if (features[481] < -0.333856f) {
                                              if (features[674] < -0.585665f) {
                                                  return 2;
                                              } else {
                                                  if (features[479] < -0.671598f) {
                                                      return 8;
                                                  } else {
                                                      return 4;
                                                  }
                                              }
                                          } else {
                                              if (features[697] < -0.304849f) {
                                                  return 1;
                                              } else {
                                                  if (features[288] < -0.200755f) {
                                                      if (features[73] < -0.536640f) {
                                                          return 7;
                                                      } else {
                                                          if (features[435] < -0.513591f) {
                                                              return 9;
                                                          } else {
                                                              return 0;
                                                          }
                                                      }
                                                  } else {
                                                      return 5;
                                                  }
                                              }
                                          }
                                      }
                                  } else {
                                      if (features[514] < -0.572573f) {
                                          if (features[384] < -0.389274f) {
                                              if (features[981] < 3.598187f) {
                                                  return 1;
                                              } else {
                                                  return 3;
                                              }
                                          } else {
                                              if (features[550] < -0.502640f) {
                                                  if (features[266] < -0.295320f) {
                                                      return 6;
                                                  } else {
                                                      return 5;
                                                  }
                                              } else {
                                                  if (features[902] < -0.095522f) {
                                                      return 9;
                                                  } else {
                                                      if (features[374] < -0.081973f) {
                                                          if (features[374] < -0.124857f) {
                                                              return 5;
                                                          } else {
                                                              if (features[682] < -0.300614f) {
                                                                  return 2;
                                                              } else {
                                                                  if (features[515] < -0.809959f) {
                                                                      return 0;
                                                                  } else {
                                                                      return 3;
                                                                  }
                                                              }
                                                          }
                                                      } else {
                                                          return 8;
                                                      }
                                                  }
                                              }
                                          }
                                      } else {
                                          if (features[37] < -0.724580f) {
                                              if (features[400] < -0.488790f) {
                                                  return 0;
                                              } else {
                                                  if (features[1010] < -0.674197f) {
                                                      return 9;
                                                  } else {
                                                      if (features[417] < -0.518198f) {
                                                          return 8;
                                                      } else {
                                                          return 7;
                                                      }
                                                  }
                                              }
                                          } else {
                                              if (features[117] < -0.153212f) {
                                                  if (features[40] < 0.290383f) {
                                                      return 3;
                                                  } else {
                                                      return 9;
                                                  }
                                              } else {
                                                  if (features[521] < -0.304191f) {
                                                      return 7;
                                                  } else {
                                                      if (features[715] < -0.274766f) {
                                                          return 2;
                                                      } else {
                                                          if (features[632] < -0.008614f) {
                                                              return 6;
                                                          } else {
                                                              return 4;
                                                          }
                                                      }
                                                  }
                                              }
                                          }
                                      }
                                  }
                              } else {
                                  if (features[409] < -0.391808f) {
                                      if (features[1021] < -0.779251f) {
                                          return 2;
                                      } else {
                                          if (features[508] < -0.007278f) {
                                              return 8;
                                          } else {
                                              return 9;
                                          }
                                      }
                                  } else {
                                      if (features[515] < -0.066547f) {
                                          if (features[567] < -0.196632f) {
                                              if (features[580] < -0.240811f) {
                                                  return 3;
                                              } else {
                                                  if (features[298] < 0.126105f) {
                                                      return 2;
                                                  } else {
                                                      return 8;
                                                  }
                                              }
                                          } else {
                                              if (features[451] < -0.013127f) {
                                                  if (features[598] < -0.220433f) {
                                                      if (features[468] < -0.173222f) {
                                                          return 4;
                                                      } else {
                                                          if (features[710] < -0.175405f) {
                                                              return 5;
                                                          } else {
                                                              return 7;
                                                          }
                                                      }
                                                  } else {
                                                      return 8;
                                                  }
                                              } else {
                                                  return 6;
                                              }
                                          }
                                      } else {
                                          if (features[452] < -0.419823f) {
                                              return 8;
                                          } else {
                                              return 4;
                                          }
                                      }
                                  }
                              }
                          } else {
                              if (features[302] < -0.206683f) {
                                  if (features[1019] < -0.094783f) {
                                      if (features[597] < -0.277424f) {
                                          if (features[451] < -0.152397f) {
                                              if (features[1021] < -0.424122f) {
                                                  if (features[793] < -0.315079f) {
                                                      if (features[1009] < -0.617909f) {
                                                          if (features[25] < -0.486122f) {
                                                              return 8;
                                                          } else {
                                                              return 3;
                                                          }
                                                      } else {
                                                          return 5;
                                                      }
                                                  } else {
                                                      return 2;
                                                  }
                                              } else {
                                                  if (features[212] < -0.279677f) {
                                                      return 0;
                                                  } else {
                                                      return 1;
                                                  }
                                              }
                                          } else {
                                              return 9;
                                          }
                                      } else {
                                          return 2;
                                      }
                                  } else {
                                      if (features[19] < 0.032613f) {
                                          if (features[702] < -0.531072f) {
                                              if (features[911] < -0.609189f) {
                                                  if (features[40] < -0.172819f) {
                                                      if (features[494] < -0.564510f) {
                                                          return 5;
                                                      } else {
                                                          return 2;
                                                      }
                                                  } else {
                                                      return 0;
                                                  }
                                              } else {
                                                  return 8;
                                              }
                                          } else {
                                              if (features[631] < -0.008275f) {
                                                  if (features[418] < 0.090960f) {
                                                      if (features[870] < 0.113361f) {
                                                          return 0;
                                                      } else {
                                                          if (features[165] < -0.516523f) {
                                                              return 0;
                                                          } else {
                                                              return 4;
                                                          }
                                                      }
                                                  } else {
                                                      return 9;
                                                  }
                                              } else {
                                                  return 6;
                                              }
                                          }
                                      } else {
                                          if (features[903] < -0.439168f) {
                                              return 5;
                                          } else {
                                              if (features[521] < -0.208375f) {
                                                  return 9;
                                              } else {
                                                  if (features[468] < -0.207930f) {
                                                      return 2;
                                                  } else {
                                                      return 0;
                                                  }
                                              }
                                          }
                                      }
                                  }
                              } else {
                                  if (features[514] < 0.230143f) {
                                      if (features[1011] < 0.094362f) {
                                          if (features[665] < -0.386034f) {
                                              if (features[11] < -0.568875f) {
                                                  return 7;
                                              } else {
                                                  if (features[27] < 0.505200f) {
                                                      if (features[37] < 0.085211f) {
                                                          if (features[1021] < -0.582725f) {
                                                              return 2;
                                                          } else {
                                                              if (features[903] < -0.244301f) {
                                                                  if (features[232] < -0.117164f) {
                                                                      return 8;
                                                                  } else {
                                                                      return 9;
                                                                  }
                                                              } else {
                                                                  return 0;
                                                              }
                                                          }
                                                      } else {
                                                          return 5;
                                                      }
                                                  } else {
                                                      return 1;
                                                  }
                                              }
                                          } else {
                                              if (features[480] < 0.322194f) {
                                                  if (features[530] < -0.695086f) {
                                                      if (features[494] < -0.749855f) {
                                                          if (features[95] < -0.503726f) {
                                                              return 9;
                                                          } else {
                                                              if (features[24] < -0.697024f) {
                                                                  return 6;
                                                              } else {
                                                                  if (features[54] < -0.449474f) {
                                                                      return 0;
                                                                  } else {
                                                                      return 2;
                                                                  }
                                                              }
                                                          }
                                                      } else {
                                                          return 3;
                                                      }
                                                  } else {
                                                      if (features[638] < 0.579028f) {
                                                          if (features[251] < 0.190449f) {
                                                              return 9;
                                                          } else {
                                                              return 7;
                                                          }
                                                      } else {
                                                          if (features[793] < -0.108095f) {
                                                              return 7;
                                                          } else {
                                                              return 8;
                                                          }
                                                      }
                                                  }
                                              } else {
                                                  if (features[456] < 0.358950f) {
                                                      return 3;
                                                  } else {
                                                      if (features[39] < -0.106375f) {
                                                          return 0;
                                                      } else {
                                                          return 4;
                                                      }
                                                  }
                                              }
                                          }
                                      } else {
                                          if (features[502] < 1.474741f) {
                                              if (features[956] < 0.466786f) {
                                                  if (features[515] < -0.173798f) {
                                                      if (features[434] < 0.112252f) {
                                                          return 2;
                                                      } else {
                                                          return 1;
                                                      }
                                                  } else {
                                                      if (features[926] < -0.501863f) {
                                                          return 4;
                                                      } else {
                                                          if (features[269] < -0.283157f) {
                                                              return 6;
                                                          } else {
                                                              if (features[503] < -0.215731f) {
                                                                  return 3;
                                                              } else {
                                                                  if (features[552] < -0.309165f) {
                                                                      return 8;
                                                                  } else {
                                                                      if (features[928] < -0.347512f) {
                                                                          return 9;
                                                                      } else {
                                                                          if (features[862] < 0.470477f) {
                                                                              return 2;
                                                                          } else {
                                                                              return 7;
                                                                          }
                                                                      }
                                                                  }
                                                              }
                                                          }
                                                      }
                                                  }
                                              } else {
                                                  if (features[780] < -0.370521f) {
                                                      return 0;
                                                  } else {
                                                      if (features[524] < 0.219283f) {
                                                          return 1;
                                                      } else {
                                                          if (features[248] < -0.082310f) {
                                                              return 3;
                                                          } else {
                                                              return 5;
                                                          }
                                                      }
                                                  }
                                              }
                                          } else {
                                              if (features[981] < 0.502229f) {
                                                  return 9;
                                              } else {
                                                  return 5;
                                              }
                                          }
                                      }
                                  } else {
                                      if (features[503] < -0.519599f) {
                                          return 4;
                                      } else {
                                          if (features[51] < -0.337789f) {
                                              if (features[274] < -0.233692f) {
                                                  return 4;
                                              } else {
                                                  return 8;
                                              }
                                          } else {
                                              if (features[389] < 0.194307f) {
                                                  if (features[799] < -0.145109f) {
                                                      if (features[701] < -0.133425f) {
                                                          if (features[230] < -0.210050f) {
                                                              return 6;
                                                          } else {
                                                              if (features[491] < 2.871783f) {
                                                                  return 5;
                                                              } else {
                                                                  return 0;
                                                              }
                                                          }
                                                      } else {
                                                          return 4;
                                                      }
                                                  } else {
                                                      return 3;
                                                  }
                                              } else {
                                                  if (features[188] < 0.135889f) {
                                                      return 7;
                                                  } else {
                                                      return 2;
                                                  }
                                              }
                                          }
                                      }
                                  }
                              }
                          }
                      } else {
                          if (features[545] < -0.088765f) {
                              if (features[1006] < 0.136234f) {
                                  if (features[411] < -0.155487f) {
                                      if (features[187] < 0.113785f) {
                                          return 8;
                                      } else {
                                          return 3;
                                      }
                                  } else {
                                      return 6;
                                  }
                              } else {
                                  if (features[485] < -0.217208f) {
                                      return 0;
                                  } else {
                                      if (features[80] < 0.345769f) {
                                          return 9;
                                      } else {
                                          if (features[8] < 0.411607f) {
                                              return 4;
                                          } else {
                                              if (features[318] < 0.025520f) {
                                                  return 8;
                                              } else {
                                                  if (features[815] < -0.043630f) {
                                                      return 6;
                                                  } else {
                                                      return 3;
                                                  }
                                              }
                                          }
                                      }
                                  }
                              }
                          } else {
                              if (features[514] < -0.656088f) {
                                  if (features[674] < -0.424793f) {
                                      return 3;
                                  } else {
                                      return 9;
                                  }
                              } else {
                                  if (features[824] < -0.344006f) {
                                      if (features[514] < 0.066808f) {
                                          return 0;
                                      } else {
                                          if (features[532] < -0.242617f) {
                                              return 4;
                                          } else {
                                              return 8;
                                          }
                                      }
                                  } else {
                                      if (features[1020] < -0.095077f) {
                                          if (features[63] < 0.951522f) {
                                              if (features[870] < -0.080882f) {
                                                  return 8;
                                              } else {
                                                  if (features[1013] < -0.285726f) {
                                                      if (features[501] < -0.487342f) {
                                                          return 4;
                                                      } else {
                                                          if (features[784] < -0.040476f) {
                                                              return 9;
                                                          } else {
                                                              return 3;
                                                          }
                                                      }
                                                  } else {
                                                      return 7;
                                                  }
                                              }
                                          } else {
                                              if (features[245] < -0.061368f) {
                                                  return 6;
                                              } else {
                                                  return 4;
                                              }
                                          }
                                      } else {
                                          if (features[979] < 0.023509f) {
                                              if (features[590] < 0.386938f) {
                                                  if (features[231] < -0.200572f) {
                                                      return 6;
                                                  } else {
                                                      return 9;
                                                  }
                                              } else {
                                                  return 5;
                                              }
                                          } else {
                                              if (features[432] < 1.697657f) {
                                                  return 3;
                                              } else {
                                                  if (features[84] < 5.188871f) {
                                                      return 2;
                                                  } else {
                                                      return 9;
                                                  }
                                              }
                                          }
                                      }
                                  }
                              }
                          }
                      }
                  } else {
                      if (features[1004] < 0.806178f) {
                          if (features[628] < 1.824452f) {
                              if (features[432] < -0.512702f) {
                                  if (features[452] < -0.636200f) {
                                      return 4;
                                  } else {
                                      return 8;
                                  }
                              } else {
                                  if (features[584] < 2.239382f) {
                                      if (features[305] < -0.089676f) {
                                          if (features[491] < -0.434641f) {
                                              return 4;
                                          } else {
                                              if (features[1013] < 0.366772f) {
                                                  return 6;
                                              } else {
                                                  return 0;
                                              }
                                          }
                                      } else {
                                          if (features[243] < 0.696274f) {
                                              if (features[27] < 5.427135f) {
                                                  return 4;
                                              } else {
                                                  return 5;
                                              }
                                          } else {
                                              return 7;
                                          }
                                      }
                                  } else {
                                      if (features[315] < 0.292531f) {
                                          return 8;
                                      } else {
                                          return 3;
                                      }
                                  }
                              }
                          } else {
                              return 8;
                          }
                      } else {
                          if (features[233] < 0.052048f) {
                              if (features[230] < -0.122871f) {
                                  return 6;
                              } else {
                                  if (features[697] < 0.016339f) {
                                      return 3;
                                  } else {
                                      if (features[61] < 4.156435f) {
                                          return 7;
                                      } else {
                                          return 9;
                                      }
                                  }
                              }
                          } else {
                              return 2;
                          }
                      }
                  }
              } else {
                  if (features[508] < 1.075692f) {
                      if (features[1] < -0.206258f) {
                          if (features[0] < -0.256011f) {
                              if (features[98] < -0.266466f) {
                                  return 5;
                              } else {
                                  if (features[74] < -0.335162f) {
                                      if (features[338] < 0.429344f) {
                                          return 2;
                                      } else {
                                          return 7;
                                      }
                                  } else {
                                      return 8;
                                  }
                              }
                          } else {
                              return 3;
                          }
                      } else {
                          if (features[12] < 1.078758f) {
                              if (features[203] < 0.284324f) {
                                  return 3;
                              } else {
                                  if (features[866] < 5.386932f) {
                                      if (features[938] < -0.563400f) {
                                          return 8;
                                      } else {
                                          if (features[570] < -0.604143f) {
                                              return 8;
                                          } else {
                                              return 7;
                                          }
                                      }
                                  } else {
                                      return 9;
                                  }
                              }
                          } else {
                              if (features[283] < 0.617823f) {
                                  return 9;
                              } else {
                                  return 4;
                              }
                          }
                      }
                  } else {
                      if (features[501] < 0.173911f) {
                          if (features[900] < 0.145084f) {
                              return 3;
                          } else {
                              if (features[666] < 0.113669f) {
                                  return 8;
                              } else {
                                  if (features[576] < 0.768714f) {
                                      return 7;
                                  } else {
                                      return 6;
                                  }
                              }
                          }
                      } else {
                          if (features[245] < 0.984120f) {
                              return 4;
                          } else {
                              return 7;
                          }
                      }
                  }
              }
          }
        }
        

int32_t DecisionTreeClassifier_predict(const float *features, int32_t features_length) {

        int32_t votes[10] = {0,};
        int32_t _class = -1;

        _class = DecisionTreeClassifier_tree_0(features, features_length); votes[_class] += 1;
    
        int32_t most_voted_class = -1;
        int32_t most_voted_votes = 0;
        for (int32_t i=0; i<10; i++) {

            if (votes[i] > most_voted_votes) {
                most_voted_class = i;
                most_voted_votes = votes[i];
            }
        }
        return most_voted_class;
    }
    #endif