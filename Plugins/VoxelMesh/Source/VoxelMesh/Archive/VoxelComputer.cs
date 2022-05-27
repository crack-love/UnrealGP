//#if UNITY_EDITOR
//using UnityEditor;
//#endif
//using UnityEngine;
//using UnityCommon;
//using System;
//using System.Collections.Generic;

///// <summary>
///// 2021-02-03 수 오후 7:55:41, 4.0.30319.42000, YONG-PC, Yong
///// </summary>
//namespace mvp7
//{
//    [Serializable][ExecuteAlways]
//    class VoxelComputer : GPUComputerMono<VoxelComputerIn, VoxelComputerOut>
//    {
//        public static VoxelComputer Instance => Singletone<VoxelComputer>.Instance;

//        #region Structs
//        struct TriangleVertex
//        {
//            public Vector3 Pos;
//            public int Tex; // tex (0~15)
//        }
//        const int TriangleVertexByte = 4 * 4;

//        struct Triangle
//        {
//            public TriangleVertex V1;
//            public TriangleVertex V2;
//            public TriangleVertex V3;

//            public TriangleVertex this[int idx] => (idx == 0) ? V1 : ((idx == 1) ? V2 : V3);
//        }
//        const int TriangleByte = TriangleVertexByte * 3;

//        [Serializable]
//        class TriangleBuffer
//        {
//            public static TriangleBuffer Empty = new TriangleBuffer();

//            public ComputeBuffer Buffer;
//            public int Length;
//        }
//        #endregion

//        [SerializeField] ComputeShader m_shader;
//        [SerializeField] List<TriangleBuffer> m_triangleBufferPool;
        
//        // Pre Compute Tools
//        Vector3Int m_bufferVertexSize; // 4의 배수일것
//        ComputeBuffer m_bufferVolumes;
//        ComputeBuffer m_bufferTextures;
//        TriangleBuffer m_bufferTriangles; // res buffer

//        // Post Compute Tools
//        Triangle[] m_triangles;
//        int[] m_meshTriangles;
//        Vector3[] m_meshVertexes;
//        Vector2[] m_meshUV0;
//        Dictionary<Vector3, int> m_vertexRegister; // vidx, cubeidx
//        Dictionary<ComputeBuffer, TriangleBuffer> m_triangleBufferDic;

//        public void OnEnable()
//        {
//            if (m_triangleBufferPool == null)
//            {
//                m_triangleBufferPool = new List<TriangleBuffer>();
//            }

//            if (m_vertexRegister == null)
//            {
//                m_vertexRegister = new Dictionary<Vector3, int>();
//            }

//            if (m_triangleBufferDic== null)
//            {
//                m_triangleBufferDic = new Dictionary<ComputeBuffer, TriangleBuffer>();
//            }
//        }

//        public void OnDisable()
//        {
//            DisposeAllBuffers();
//        }

//        TriangleBuffer GetTriangleBuffer(int maxLength)
//        {
//            // find more length buffer than param
//            int size = m_triangleBufferPool.Count;
//            for (int i = 0; i < size; ++i)
//            {
//                var curr = m_triangleBufferPool[i];

//                if (curr != null &&
//                    curr.Length >= maxLength)
//                {
//                    // remove
//                    m_triangleBufferPool[i] = TriangleBuffer.Empty;

//                    m_triangleBufferDic.Add(curr.Buffer, curr);
//                    return curr;
//                }
//            }

//            // new
//            var res = new TriangleBuffer()
//            {
//                Buffer = new ComputeBuffer(maxLength, TriangleByte, ComputeBufferType.Append),
//                Length = maxLength,
//            };

//            m_triangleBufferDic.Add(res.Buffer, res);

//            return res;
//        }

//        void ReturnTriangleBuffer(TriangleBuffer buffer)
//        {
//            int size = m_triangleBufferPool.Count;
//            for (int i = 0; i < size; ++i)
//            {
//                var curr = m_triangleBufferPool[i];

//                if (curr == TriangleBuffer.Empty)
//                {
//                    m_triangleBufferPool[i] = buffer;
//                    m_triangleBufferDic.Remove(buffer.Buffer);
//                    return;
//                }
//            }

//            m_triangleBufferPool.Add(buffer);
//            m_triangleBufferDic.Remove(buffer.Buffer);
//        }

//        void InitializeBuffers(VoxelComputerIn input) // three compute buffer, and three mesh buffer
//        {
//            var newVertexSize = input.VertexSize;
//            var newSerialVertexSize = newVertexSize.Multiply();
//            var newSerialVoxelSize = newVertexSize.Subtract(1).Multiply();

//            newSerialVertexSize += newSerialVertexSize % 4; // 4의 배수
//            newSerialVoxelSize += newSerialVoxelSize % 4;

//            int newBufferVertexByteSize = newSerialVertexSize / 4; // byte stride = 4
//            int newBufferTriangleSize = newSerialVoxelSize * 5;    // 1복셀당 최대 5 트라이엥글
//            int newBufferMeshVertexSize = newBufferTriangleSize * 3;  // 1트라이엥글당 최대 3 버택스

//            // new allocation
//            if (newVertexSize.MoreAny(m_bufferVertexSize))
//            {
//                DisposeBuffers();

//                m_bufferVertexSize = newVertexSize;
//                m_bufferVolumes = new ComputeBuffer(newBufferVertexByteSize, 4, ComputeBufferType.Raw);
//                m_bufferTextures = new ComputeBuffer(newBufferVertexByteSize, 4, ComputeBufferType.Raw);

//                m_triangles = new Triangle[newBufferTriangleSize];
//                m_meshTriangles = new int[newBufferMeshVertexSize];
//                m_meshVertexes = new Vector3[newBufferMeshVertexSize];
//                m_meshUV0 = new Vector2[newBufferMeshVertexSize];
//            }

//            // new output buffer
//            m_bufferTriangles = GetTriangleBuffer(newBufferTriangleSize);
            
//            // clear buffers
//            m_bufferVolumes.SetCounterValue(0);
//            m_bufferTextures.SetCounterValue(0);
//            m_bufferTriangles.Buffer.SetCounterValue(0);
//        }

//        void DisposeBuffers()
//        {
//            m_bufferVolumes?.Dispose();
//            m_bufferTriangles?.Buffer?.Dispose();
//            m_bufferVolumes = null;
//            m_bufferTriangles = null;
//            m_bufferVertexSize = Vector3Int.zero;
//        }

//        void DisposeAllBuffers()
//        {
//            DisposeBuffers();

//            // dispose pool
//            foreach (var tb in m_triangleBufferPool)
//            {
//                tb.Buffer?.Dispose();
//            }
//            m_triangleBufferPool.Clear();

//            // dispose using
//            foreach (var key in m_triangleBufferDic.Keys)
//            {
//                key?.Dispose();
//            }
//            m_triangleBufferDic.Clear();
//        }

//        protected override void PreProcess(BatchInfo src)
//        {
//            // Validate input
//            var input = src.Input;
//            if (input.VertexSize.LessAny(1)) throw new ArgumentException("VertexSize");
//            if (input.VertexGap.LessSameAny(0)) throw new ArgumentException("VertexGap");
//            if (input.Volumes == null) throw new ArgumentException("Volumes");
//            if (input.Textures == null) throw new ArgumentException("Textures");
//            if (input.IsWrap) input.VertexSize = input.VertexSize.Add(2); // changing input

//            // shdaer
//            if (!m_shader)
//            {
//                throw new Exception("No Shader");
//            }
//            src.Shader = m_shader;

//            // kernel
//            var kernel = input.IsWrap ? 1 : 0;
//            src.KernelIndex = kernel;

//            // dataSize
//            src.DataSize = input.VertexSize;

//            // Initialize buffers
//            InitializeBuffers(input);

//            // Set Buffers
//            m_bufferVolumes.SetData(input.Volumes);
//            m_bufferTextures.SetData(input.Textures);
//            m_shader.SetInts("_VertexSize", input.VertexSize.x, input.VertexSize.y, input.VertexSize.z);
//            m_shader.SetFloats("_LeftBot", input.LeftBot.x, input.LeftBot.y, input.LeftBot.z);
//            m_shader.SetFloats("_VertexGap", input.VertexGap.x, input.VertexGap.y, input.VertexGap.z);
//            m_shader.SetBuffer(kernel, "_Volumes", m_bufferVolumes);
//            m_shader.SetBuffer(kernel, "_Textures", m_bufferTextures);
//            m_shader.SetBuffer(kernel, "_Triangles", m_bufferTriangles.Buffer);
//            m_shader.SetBool("_IsLittleEndian", BitConverter.IsLittleEndian);

//            src.CompletionBuffer = m_bufferTriangles.Buffer;
//        }

//        protected override VoxelComputerOut PostProcess(BatchInfo src)
//        {
//            m_vertexRegister.Clear();

//            // Get Data
//            int tcnt = src.CompletionBuffer.GetData<Triangle>(m_triangles);
            
//            // process triangle
//            int vidx = 0; // vidx == vcnt
//            int tvidx = 0;
//            for (int i = 0; i < tcnt; ++i)
//            {
//                // add to vertex/triangle/uv
//                // remove duplicate vertex
//                // smooting or edging 
//                AddVertex(m_triangles[i].V1, tvidx, ref vidx);
//                AddVertex(m_triangles[i].V2, tvidx + 1, ref vidx);
//                AddVertex(m_triangles[i].V3, tvidx + 2, ref vidx);

//                tvidx += 3;
//            }

//            // Clear Mesh
//            var mesh = src.Input.Mesh;
//            if (!mesh)
//            {
//                mesh = new Mesh();
//                src.Input.Mesh = mesh;
//            }
//            mesh.Clear(true);

//            // Set Mesh
//            if (tcnt > 10000)
//            {
//                mesh.indexFormat = UnityEngine.Rendering.IndexFormat.UInt32;
//            }
            
//            mesh.SetVertices(m_meshVertexes, 0, vidx);
//            mesh.SetTriangles(m_meshTriangles, 0, tcnt * 3, 0);
//            mesh.SetUVs(0, m_meshUV0, 0, vidx);

//            //mesh.SetUVs(1, _meshUV1, 0, vcnt);

//            mesh.RecalculateBounds();
//            mesh.RecalculateNormals();
//            mesh.RecalculateTangents();
            
//            // todo : edgenormal recalc.
//            // 

            
//            // dispose
//            ReturnTriangleBuffer(m_triangleBufferDic[src.CompletionBuffer]);

//            var output = new VoxelComputerOut()
//            {
//                Mesh = mesh,
//                Target = src.Input.Target,
//            };

//            return output;
//        }

//        void AddVertex(TriangleVertex v, int tvidx, ref int vidx)
//        {
//            var pos = v.Pos;
//            var tex = v.Tex;

//            // registed vertex
//            if (m_vertexRegister.TryGetValue(pos, out int foundVidx))
//            {
//                // add triangle
//                m_meshTriangles[tvidx] = foundVidx;
//            }
//            // new vertex
//            else
//            {
//                m_vertexRegister.Add(pos, vidx);

//                // vertex
//                m_meshVertexes[vidx] = pos;

//                // tex
//                m_meshUV0[vidx].x = tex;
//                //_meshUV0[vidx].y = tex;

//                // triangle
//                m_meshTriangles[tvidx] = vidx;

//                vidx += 1;
//            }
//        }
//    }

//    public struct VoxelComputerIn
//    {
//        public byte[] Volumes;
//        public byte[] Textures;
//        public Vector3Int VertexSize;
//        public Vector3 VertexGap;
//        public bool IsWrap;
//        public object Target;
//        public Mesh Mesh;
//        public Vector3 LeftBot;
//    }

//    public struct VoxelComputerOut
//    {
//        public object Target;
//        public Mesh Mesh;
//    }

//}