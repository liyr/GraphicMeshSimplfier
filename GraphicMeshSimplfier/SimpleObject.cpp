#define _CRT_SECURE_NO_WARNINGS

#include "SimpleObject.h"
#include <vector>
#include <queue>
#include "Vec4f.h"
#include "Matrix.h"
#include <set>
#include <map>

double calOptimal(Matrix q1, Vec4f &a, SimpleOBJ::Vec3f &c, SimpleOBJ::Vec3f &d)
{
    double ans = q1.det3();
    if (abs(ans) > 1e-2)
    {
        a[0] = -q1.det3(0) / ans;
        a[1] = -q1.det3(1) / ans;
        a[2] = -q1.det3(2) / ans;
        return a | (q1 * a);
    }
    else
    {
        a[0] = ((c + d) / 2)[0];
        a[1] = ((c + d) / 2)[1];
        a[2] = ((c + d) / 2)[2];
        return a | (q1 * a);
    }
}

struct cmp {
    static Matrix *Q;
    static SimpleOBJ::Vec3f *m_pVertexList;
    bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) const
    {
        Matrix Q1 = Q[a.first] + Q[a.second], Q2 = Q[b.first] + Q[b.second];
        Vec4f m(0, 0, 0), n(0, 0, 0);
        return  calOptimal(Q1, m, m_pVertexList[a.first], m_pVertexList[a.second]) > calOptimal(Q2, m, m_pVertexList[b.first], m_pVertexList[b.second]);
    }
};
Matrix *cmp::Q = 0;
SimpleOBJ::Vec3f *cmp::m_pVertexList = 0;

Matrix mult(const Vec4f& p1, const Vec4f& p2)
{
    Matrix res;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            res.ele_[i][j] = p1[i] * p2[j];
    return res;

}

namespace SimpleOBJ
{
    CSimpleObject::CSimpleObject(void)
    {
        m_nVertices = -1;
        m_nTriangles = -1;
        m_pTriangleList = NULL;
        m_pVertexList = NULL;
    }

    CSimpleObject::~CSimpleObject(void)
    {
        Destroy();
    }

    void CSimpleObject::Destroy()
    {
        if(m_pTriangleList)
            delete []m_pTriangleList;
        if(m_pVertexList)
            delete []m_pVertexList;

        m_nVertices = -1;
        m_nTriangles = -1;
        m_pVertexList = NULL;
        m_pTriangleList = NULL;
    }

    bool CSimpleObject::LoadFromObj(const char* fn)
    {
        FILE* fp;
        fopen_s(&fp, fn, "r");
        if(fp==NULL)
        {
            printf("Error: Loading %s failed.\n",fn);
            return false;
        }
        else
        {
            if(Parse(fp))
            {
                printf("Loading from %s successfully.\n",fn);
                printf("Vertex Number = %d\n",m_nVertices);
                printf("Triangle Number = %d\n",m_nTriangles);
                fclose(fp);
                return true;
            }
            else
            {
                fclose(fp);
                return false;
            }
        }
    }

    bool CSimpleObject::Parse(FILE* fp)
    {
        
        char buf[256];
        int nVertices,nTriangles;
        std::vector<Vec3f>          vecVertices;
        std::vector<Array<int,3> >  vecTriangles;

        nVertices = 0;
        nTriangles = 0;
        vecVertices.clear();
        vecTriangles.clear();
        int lineNumber = 0; 

        while(fscanf(fp, "%s", buf) != EOF)
        {
            lineNumber ++;
            switch(buf[0])
            {
            case '#':				/* comment */
                /* eat up rest of line */
                fgets(buf, sizeof(buf), fp);
                break;
            case 'v':				/* v, vn, vt */
                switch(buf[1])
                {
                case '\0':			    /* vertex */
                    {
                        Vec3f vP;
                        if(fscanf(fp, "%f %f %f", 
                            &vP.x, 
                            &vP.y, 
                            &vP.z)==3)
                        {
                            nVertices++;
                            vecVertices.push_back(vP);
                        }
                        else 
                        {
                            printf("Error: Wrong Number of Values(Should be 3). at Line %d\n",lineNumber);
                            return false;
                        }
                    }
                    break;
                default:
                    /* eat up rest of line */
	                fgets(buf, sizeof(buf), fp);
                    break;
                }
                break;

            case 'f':				/* face */
                {
                    int v,n,t;
                    Array<int,3> vIndices;
                    if(fscanf(fp, "%s", buf)!=1)
                    {
                        printf("Error: Wrong Face at Line %d\n",lineNumber);
                        return false;
                    }
                    
                    /* can be one of %d, %d//%d, %d/%d, %d/%d/%d %d//%d */
                    if (strstr(buf, "//"))
                    {
                        /* v//n */
                        if( sscanf(buf, "%d//%d", &vIndices[0],&n) ==2  &&
                            fscanf(fp, "%d//%d", &vIndices[1], &n) ==2  &&
                            fscanf(fp, "%d//%d", &vIndices[2], &n) ==2)
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }

                    }
                    else if (sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3)
                    {
                        /* v/t/n */
                        vIndices[0] = v;
                        if( fscanf(fp, "%d/%d/%d", &vIndices[1], &t, &n) ==3 &&
                            fscanf(fp, "%d/%d/%d", &vIndices[2], &t, &n) ==3 )
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }
                    }
                    else if (sscanf(buf, "%d/%d", &v, &t) == 2)
                    {
                        /* v/t */
                        vIndices[0] = v;
                        if( fscanf(fp, "%d/%d", &vIndices[1], &t) ==2 &&
                            fscanf(fp, "%d/%d", &vIndices[2], &t) ==2 )
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }
                    }
                    else
                    {
                        /* v */
                        if( sscanf(buf, "%d", &vIndices[0]) ==1 && 
                            fscanf(fp, "%d", &vIndices[1])  ==1 &&
                            fscanf(fp, "%d", &vIndices[2])  ==1 )
                        {
                            nTriangles++;
                            vecTriangles.push_back(vIndices);
                        }
                        else
                        {
                            printf("Error: Wrong Face at Line %d\n",lineNumber);
                            return false;
                        }
                    }

                }

                break;

            default:
                /* eat up rest of line */
                fgets(buf, sizeof(buf), fp);
                break;
            }
        }
        
        if(CheckParse(vecVertices.size(),vecTriangles))
        {
            Destroy();
            
            m_nVertices = vecVertices.size();
            m_nTriangles = vecTriangles.size();            
            m_pVertexList = new Vec3f[m_nVertices];
            m_pTriangleList = new Array<int,3> [m_nTriangles];

            for(int i=0;i<m_nVertices;i++)
                m_pVertexList[i] = vecVertices[i];
            for(int i=0;i<m_nTriangles;i++)
            {
                for(int j=0;j<3;j++)
                m_pTriangleList[i][j] = vecTriangles[i][j] - 1;
            }

            return true;
        }
        else
            return false;
    }

    bool CSimpleObject::CheckParse(int nVertices,std::vector<Array<int,3> > & vecTriangles)
    {
        for(int i=0;i<vecTriangles.size();i++)
        {
            Array<int,3> & vIndices = vecTriangles[i];
            for(int j=0;j<vIndices._len;j++)
                if(vIndices[j]<=0||vIndices[j]>nVertices)
                {
                    printf("Error: The vertex index of Face %d has exceeded vertex number %d\n",i,nVertices);
                    return false;
                }
        }

        return true;
    }

    bool CSimpleObject::SaveToObj(const char* fn)
    {
        if(!IsLoaded())
        {
            printf("Error: Object is not initialized.\n",fn);
            return false;
        }
        
        FILE* fp = fopen(fn,"w");
        if(fp==NULL)
        {
            printf("Error: Failed opening %s to write\n",fn);
            return false;
        }

        fprintf(fp,"# %d vertices\n",m_nVertices);
        for(int i=0;i<m_nVertices;i++)
            fprintf(fp,"v %f %f %f\n",  m_pVertexList[i].x,
                                        m_pVertexList[i].y,
                                        m_pVertexList[i].z);

        fprintf(fp,"# %d triangles\n",m_nTriangles);
        for(int i=0;i<m_nTriangles;i++)
            fprintf(fp,"f %d %d %d\n",  m_pTriangleList[i][0] + 1,
                                        m_pTriangleList[i][1] + 1,
                                        m_pTriangleList[i][2] + 1);

        fclose(fp);
        
        printf("Writing to %s successfully\n",fn);
        return true;

    }

    Vec4f CSimpleObject::calNormal(int tri_num)
    {
        auto v0 = m_pVertexList[m_pTriangleList[tri_num][0]],
            v1 = m_pVertexList[m_pTriangleList[tri_num][1]],
            v2 = m_pVertexList[m_pTriangleList[tri_num][2]];
        Vec3f res = ((v1 - v0) % (v2 - v0));
        res.Normalize();
        double d = -res | v0;
        Vec4f ans(res[0], res[1], res[2], d);
        return ans;
    }


    CSimpleObject CSimpleObject::simplify(const double ratio)
    {
        std::vector<Vec3f>          vecVertices;
        std::vector<Array<int, 3> >  vecTriangles;
        std::map<int, std::set<std::pair<int,int>>> ver2tri;
        for(int i = 0; i < m_nTriangles; i++)
        {
            vecTriangles.push_back(m_pTriangleList[i]);
            ver2tri[m_pTriangleList[i][0]].insert({ i,0 });
            ver2tri[m_pTriangleList[i][1]].insert({ i,1 });
            ver2tri[m_pTriangleList[i][2]].insert({ i,2 });
        }
        for(int i = 0; i < m_nVertices; ++i)
        {
            vecVertices.push_back(m_pVertexList[i]);
        }


        std::set<std::pair<int, int>> pairs;
        Matrix *Q = new Matrix[m_nVertices];
        for (int i = 0; i < m_nTriangles; ++i)
        {
            auto x = calNormal(i);
            Matrix q = mult(x, x);

            Q[m_pTriangleList[i][0]] += q;
            Q[m_pTriangleList[i][1]] += q;
            Q[m_pTriangleList[i][2]] += q;
            int tx = m_pTriangleList[i][0];
            int ty = m_pTriangleList[i][1];
            int tz = m_pTriangleList[i][2];
            int stx = std::max(std::max(tx, ty), tz);
            int stz = std::min(std::min(tx, ty), tz);
            int sty = tx + ty + tz - stx - stz;
            pairs.insert({ stx,stz });
            pairs.insert({ stx,sty });
            pairs.insert({ sty,stz });
        }
        cmp::Q = Q;
        cmp::m_pVertexList = m_pVertexList;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp> pq;

        for(auto &ele: pairs)
        {
            pq.push(ele);
        }
        
        for(int i = 0; i < m_nVertices * ratio; ++i)
        {
            auto aim = pq.top();
            pq.pop();
            Vec4f newVer(0, 0, 0);
            Matrix Q1 = Q[aim.first] + Q[aim.second];
            calOptimal(Q1, newVer, vecVertices[aim.first], vecVertices[aim.second]);
            vecVertices.push_back(newVer);
            for(auto &tri:ver2tri[aim.first])
            {
                vecTriangles[tri.first][tri.second] = vecVertices.end() - vecVertices.begin() - 1;
            }
            for (auto &tri : ver2tri[aim.second])
            {
                vecTriangles[tri.first][tri.second] = vecVertices.end() - vecVertices.begin() - 1;
            }

        }
        for (auto it = vecTriangles.begin(); it != vecTriangles.end();)
        {
            if ((*it)[0] == (*it)[1] || (*it)[0] == (*it)[2] || (*it)[1] == (*it)[2])
                it = vecTriangles.erase(it);
            else
                ++it;
        }

        CSimpleObject output;
        output.m_nVertices = vecVertices.end() - vecVertices.begin();
        output.m_nTriangles = vecTriangles.end() - vecTriangles.begin();


        output.m_pVertexList = new Vec3f[output.m_nVertices];
        output.m_pTriangleList = new Array<int,3>[output.m_nTriangles];

        for(int i = 0; i < output.m_nVertices; ++i)
        {
            output.m_pVertexList[i] = vecVertices[i];
        }
        for (int i = 0; i < output.m_nTriangles; ++i)
        {
            output.m_pTriangleList[i] = vecTriangles[i];
        }
        return output;
    }
}


