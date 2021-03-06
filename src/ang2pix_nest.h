// Copyright (C) 2009 Marc Betoule

// This file is part of SkOP.

// SkOP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
  
// SkOP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with SkOP.  If not, see <http://www.gnu.org/licenses/>.

"uniform sampler2D tex1,tex2,tex3;\n"
"uniform int nside;\n"
"uniform float dist, theta0, phi0, minv, maxv;\n"
"const float pi = 3.141592653589793238462643383279502884197;\n"
"mat3 rot = mat3(cos(phi0)*cos(theta0), -sin(phi0)*cos(theta0), sin(theta0),\n"
"sin(phi0), cos(phi0), 0,\n"
"		-sin(theta0)*cos(phi0),sin(theta0)*sin(phi0),cos(theta0));\n"
"float nsidef = float(nside);\n"
"float nsmax=8192.0;\n"
"vec3 col0 = vec3(0,0,0.5);\n"
"vec3 col1 = vec3(0,0,1);\n"
"vec3 col2 = vec3(0,1,1);\n"
"vec3 col3 = vec3(1,1,0);\n"
"vec3 col4 = vec3(1,0.33,0);\n"
"vec3 col5 = vec3(0.5,0,0);\n"
"float diff=maxv-minv;\n"
"float val1=0.15*diff+minv;\n"
"float val2=0.4*diff+minv;\n"
"float val3=0.7*diff+minv;\n"
"float val4=0.9*diff+minv;\n"
"//vec2 coord2thetaphi(vec2 coor){\n"
"  //vec2 thetaphi = vec2(acos(coor.y),asin(coor.x/sin(acos(coor.y))));\n"
"  //vec3 coord=vec3(cos(thetaphi.y)*sin(thetaphi.x),\n"
"  //sin(thetaphi.y)*sin(thetaphi.x),\n"
"  //cos(thetaphi.x));\n"
"  \n"
"  //coord = rot*coord;\n"
"  //thetaphi = vec2(acos(coord.z),atan(coord.y,coord.x));\n"
"  //return thetaphi;\n"
"//  return coor;\n"
"//}\n"
"\n"
"vec2 coord2zphi(vec2 coor){\n"
"  vec2 thetaphi = vec2(acos(coor.y),asin(coor.x/sin(acos(coor.y))));\n"
"  vec3 coord=vec3(cos(thetaphi.y)*sin(thetaphi.x),\n"
"  sin(thetaphi.y)*sin(thetaphi.x),\n"
"  cos(thetaphi.x));\n"
"  \n"
"  coord = rot*coord;\n"
"  thetaphi = vec2(coord.z,atan(coord.y,coord.x));\n"
"  return thetaphi;\n"
"  return coor;\n"
"}\n"
"\n"
"\n"
"vec4 jet(float val){\n"
"  val = clamp(val,minv,maxv);\n"
"  vec3 res = step(minv, val) * step(0.0, val1-val)\n"
"    * mix(col0,col1,(val-minv)/(val1-minv));\n"
"  res += step(val1, val) * step(0.0, val2-val)\n"
"    * mix(col1,col2,(val-val1)/(val2-val1));\n"
"  res += step(val2, val) * step(0.0, val3-val)\n"
"    * mix(col2,col3,(val-val2)/(val3-val2));\n"
"  res += step(val3, val) * step(0.0, val4-val)\n"
"    * mix(col3,col4,(val-val3)/(val4-val3));\n"
"  res += step(val4, val) * step(0.0, maxv-val)\n"
"    * mix(col4,col5,(val-val4)/(maxv-val4));\n"
"  return vec4(res,0.0);\n"
"}\n"
"\n"
"void main(){\n"
"  vec2 texco = 2.0*gl_TexCoord[0].st-vec2(1.0,1.0);\n"
"  texco = dist * texco;\n"
"  if(length(texco)<=1.0){\n"
"    float tt, za;\n"
"      {\n"
"	vec2 zphi = coord2zphi(texco);\n"
"	texco.y = zphi.x;\n"
"	za = abs(texco.y);\n"
"	tt = mod(zphi.y,2.0*pi)*2.0/pi;\n"
"      }\n"
"          int face_num, ix,iy;\n"
"    if(za <= 2./3.){\n"
"      float temp1 = nsmax*(0.5+tt);\n"
"      float temp2 = nsmax*texco.y*0.75;\n"
"      int jp = int(temp1-temp2);\n"
"      int jm = int(temp1+temp2);\n"
"      int ifp = int(float(jp) / nsmax);\n"
"      int ifm = int(float(jm) / nsmax);\n"
"      if(ifp == ifm){\n"
"	face_num = (ifp==4) ? 4: ifp+4;\n"
"      }\n"
"      else if(ifp < ifm){\n"
"	face_num = ifp;\n"
"      }\n"
"      else{\n"
"	face_num = ifm+8;\n"
"      }\n"
"      ix = int(mod(float(jm),nsmax));\n"
"      iy = int(mod(float(jp),nsmax));\n"
"      iy = int(nsmax)-iy;\n"
"      iy = iy -1;\n"
"    }\n"
"    else{\n"
"      float tp = fract(tt);\n"
"      float tmp = nsmax*sqrt(3.0*(1.0-za));\n"
"      int jp = int(tp*tmp);\n"
"      int jm = int((1.0-tp)*tmp);\n"
"      \n"
"      jp = int(clamp(float(jp),0.0,nsmax-1.0));\n"
"      jm = int(clamp(float(jm),0.0,nsmax-1.0));\n"
"      if(texco.y >= 0.0){\n"
"	face_num = int(tt);  //in {0,3}\n"
"	ix = int(nsmax) - jm - 1;\n"
"	iy = int(nsmax) - jp - 1;\n"
"      }\n"
"      else{\n"
"	face_num = int(tt) + 8; // in {8,11}\n"
"        ix =  jp;\n"
"        iy =  jm;\n"
"      }\n"
"    }\n"
"    ix = ix * nside / int(nsmax);\n"
"    iy = iy * nside / int(nsmax);\n"
"    gl_FragColor=vec4(ix,iy,0,1.0);\n"
"    if(face_num < 4){\n"
"      int itex = int(mod(float(face_num),4.0));\n"
"      int xf = int(mod(float(itex),2.0));\n"
"      xf = xf * nside + ix;\n"
"      int yf = int(itex/2);\n"
"      yf = yf * nside + iy;\n"
"      vec2 ij = vec2(xf,yf)/(2*nsidef);\n"
"      \n"
"      float valvec = texture2D(tex1, ij.xy).x;\n"
"      gl_FragColor = jet(valvec);\n"
"      //gl_FragColor=valvec;\n"
"      //gl_FragColor=vec4(valvec.w, 0.0, 0.0,1.0);\n"
"/*       gl_FragColor=vec4(ij.x / (2.0*nside),ij.y / (2.0*nside),0,1.0); */\n"
"    }\n"
"    \n"
"    else if(face_num < 8){\n"
"      int itex = int(mod(float(face_num),4.0));\n"
"      int xf = int(mod(float(itex),2.0));\n"
"      xf = xf * nside + ix;\n"
"      int yf = int(itex/2);\n"
"      yf = yf * nside + iy;\n"
"      vec2 ij = vec2(xf,yf);\n"
"      \n"
"      float valvec = texture2D(tex2, ij/(2*nsidef)).x;\n"
"      gl_FragColor = jet(valvec);\n"
"    }\n"
"    else{\n"
"      int itex = int(mod(float(face_num),4.0));\n"
"      int xf = int(mod(float(itex),2.0));\n"
"      xf = xf * nside + ix;\n"
"      int yf = int(itex/2);\n"
"      yf = yf * nside + iy;\n"
"      vec2 ij = vec2(xf,yf);\n"
"      \n"
"      float valvec = texture2D(tex3, ij/(2*nsidef)).x;\n"
"      gl_FragColor = jet(valvec);\n"
"    }\n"
"  }\n"
"  else{\n"
"   gl_FragColor=vec4(0.0,0,0,1.0);\n"
"  }\n"
"  //gl_FragColor=texture2D(tex, texco);\n"
"  //gl_FragColor=vec4(texco,0,1.0);\n"
"  //gl_FragColor=vec4(gl_TexCoord[0].st,0,1.0);\n"
"  //gl_FragColor=vec4(texture2D(tex, gl_TexCoord[0].st));\n"
"  //gl_FragColor=vec4(1.0,0,0,1.0);\n"
"}\n"
