<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item>
                    <i class="el-icon-lx-cascades"></i> 学生人脸库
                </el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <div class="handle-box">
                <el-button
                    type="danger"
                    icon="el-icon-delete"
                    class="handle-del mr10"
                    @click="delAllSelection"
                >批量删除</el-button>

                <el-select v-model="selected" placeholder="查询条件" class="handle-select mr10">
                    <el-option key="查学号" label="学号" value="0"></el-option>
                    <el-option key="查姓名" label="姓名" value="1"></el-option>
                </el-select>

                <el-input
                    v-model="query.request"
                    v-if="selected==='0'"
                    placeholder="输入学号"
                    class="handle-input mr10"
                    @keyup.enter.native="handleSearch"
                    id="messageInput"
                    v-on:input="inputFunc"
                ></el-input>
                <!-- @keyup.enter 但是若在组件框架中写需要加.native -->
                <el-input
                    v-model="query.request"
                    v-else
                    placeholder="输入姓名"
                    class="handle-input mr10"
                    @keyup.enter.native="handleSearch"
                    id="messageInput"
                    v-on:input="inputFunc"
                ></el-input>

                <el-button
                    v-if="showOrNot"
                    type="warning"
                    icon="el-icon-close"
                    @click="handleClear"
                >清除</el-button>
                <el-button type="primary" icon="el-icon-search" @click="handleSearch">搜索</el-button>
                <el-button type="success" icon="el-icon-circle-plus" @click="handleAdd">添加学生人脸</el-button>
                <el-button type="info" icon="el-icon-download" @click="handleUpload">更新学生人脸</el-button>
            </div>
            <el-table
                :data="tableData"
                border
                class="table"
                ref="multipleTable"
                header-cell-class-name="table-header"
                @selection-change="handleSelectionChange"
            >
                <el-table-column type="selection" width="55" align="center"></el-table-column>
                <el-table-column prop="studentNumber" label="学号" align="center"></el-table-column>
                <el-table-column prop="studentName" label="姓名" align="center"></el-table-column>
                <el-table-column prop="studentSex" label="性别" width="55" align="center">
                    <!-- 打印￥的模板 -->
                    <!-- <template slot-scope="scope">￥{{scope.row.money}}</template> -->
                </el-table-column>
                <el-table-column prop="groupId" label="组id" align="center"></el-table-column>

                <el-table-column prop="logId" label="请求标识码" align="center"></el-table-column>
                <!-- <el-table-column prop="faceToken" label="图片标识码" align="center"></el-table-column> -->

                <!-- <el-table-column label="状态" align="center">
                    <template slot-scope="scope">
                        <el-tag
                            :type="scope.row.state==='成功'?'success':(scope.row.state==='失败'?'danger':'')"
                        >{{scope.row.state}}</el-tag>
                    </template>
                </el-table-column>-->

                <el-table-column prop="time" label="操作时间" align="center"></el-table-column>

                <el-table-column label="人脸(查看大图)" align="center">
                    <!-- scope.row  当前行的数据对象 -->
                    <template slot-scope="scope">
                        <el-image
                            class="table-td-thumb"
                            :src="scope.row.face"
                            :preview-src-list="[scope.row.face]"
                        ></el-image>
                    </template>
                </el-table-column>
                <el-table-column label="操作" width="180" align="center">
                    <template slot-scope="scope">
                        <el-button
                            type="text"
                            icon="el-icon-more"
                            class="blue"
                            @click="handleMore(scope.$index, scope.row)"
                        >详情</el-button>
                        <el-button
                            type="text"
                            icon="el-icon-delete"
                            class="red"
                            @click="handleDelete(scope.$index, scope.row)"
                        >删除</el-button>
                    </template>
                </el-table-column>
            </el-table>
            <div class="pagination">
                <el-pagination
                    background
                    layout="total, prev, pager, next"
                    :current-page="query.currentPage"
                    :page-size="query.pageSize"
                    :total="query.pageTotal"
                    @current-change="handlePageChange"
                ></el-pagination>
            </div>
        </div>
        <!-- 编辑详情框 -->
        <el-dialog title="个人信息" :visible.sync="moreVisible" width="30%">
            <el-form ref="form" :model="form" label-width="70px">
                <el-form-item label="班号">
                    <el-input v-model="form.studentClass" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="学号">
                    <el-input v-model="form.studentNumber" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="姓名">
                    <el-input v-model="form.studentName" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="性别">
                    <el-input v-model="form.studentSex" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="专业">
                    <el-input v-model="form.profession" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="身份证号">
                    <el-input v-model="form.cardNo" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="加入时间">
                    <el-input v-model="form.joinTime" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="头像">
                    <el-input v-model="form.studentAvatar" readonly="readonly"></el-input>
                </el-form-item>
            </el-form>
            <span slot="footer" class="dialog-footer">
                <el-button @click="moreVisible = false">取 消</el-button>
                <el-button type="primary" @click="moreVisible = false">确 定</el-button>
            </span>
        </el-dialog>
    </div>
</template>

<script>
import { fetchData, AvatarData } from '../../api/index';
export default {
    name: 'basetable',
    data() {
        return {
            query: {
                address: '',
                name: '',
                currentPage: 1,
                pageSize: 5,
                pageTotal: 0,
                request: ''
            },
            requestAddr: '',
            selected: '0', //注意数据格式的转换，否则会导致不正常
            tableData: [],
            multipleSelection: [],
            delList: [],
            editVisible: false,
            moreVisible: false,
            addVisible: false,
            showOrNot: false,
            form: {},
            formAdd: {},
            defaultAvatar: {},
            idx: -1,
            id: -1
        };
    },
    created() {
        this.getData(); //渲染
        AvatarData(this.defaultAvatar).then((res) => {
            // console.log(res.avatar[0]);
            this.defaultAvatar = res.avatar[0].base64;
        });
    },

    methods: {
        // 获取后台数据
        getData() {
            const that = this;
            //axios的get请求,//使用spread方法处理响应数组结果
            this.$axios
                .get('/api/student/page?currentPage=' + this.query.currentPage)
                .then((res) => {
                    //  console.log(res);
                    this.tableData = res.data.data.records;
                    this.query.currentPage = res.data.data.current;
                    this.query.pageTotal = res.data.data.total;
                    this.query.pageSize = res.data.data.size;
                    console.log('请求后台数据结果', res.data.data);
                })
                .catch((err) => {
                    console.log(err);
                });
        },
        //清除搜索框
        handleClear() {
            this.query.request = '';
            this.showOrNot = false;
            this.getData();
        },
        //监听事件-输入框
        inputFunc(e) {
            if (this.query.request == '') {
                this.showOrNot = false;
                this.getData();
            } else {
                this.showOrNot = true;
            }
            // this.inputData = { value }; //把数据存入inputData
            // console.log('检测到变化'+this.query.request);
        },
        // 触发搜索按钮
        handleSearch() {
            // console.log(this.query.request);//打印输入搜索的值
            this.tableData = [];
            const that = this;
            const findByID = '/api/student/findStudentByID/';
            const findByName = '/api/student/findStudentByName/';
            console.log(this.selected);
            if (this.query.request != '') {
                //
                if (this.selected == 0) {
                    this.requestAddr = findByID;
                    this.findStudentRequest(this.requestAddr);
                } else {
                    this.requestAddr = findByName;
                    this.findStudentRequest(this.requestAddr);
                }
            } else {
                this.$message.error(`请正确输入查询内容`);
                this.getData();
            }
        },
        findStudentRequest(val) {
            // this.$set(this.query, 'currentPage', 1);
            const that = this;
            this.tableData = [];
            this.$axios
                .get(val + this.query.request)
                .then((res) => {
                    console.log(res);
                    if (res.data[0] == null) {
                        this.$message.error(`无记录`);
                        that.query.currentPage = 0;
                        that.query.pageTotal = res.data.length;
                        that.query.pageSize = res.data.length;
                    } else {
                        that.tableData = res.data;
                        that.query.currentPage = 1;
                        that.query.pageTotal = res.data.length;
                        that.query.pageSize = res.data.length;
                        // console.log('请求后台数据结果', res.data);
                    }
                })
                .catch((err) => {
                    console.log(err);
                    if (err.response.status === 400) {
                        this.$message.error(`请求错误！请正确输入查询内容`);
                    }
                });
        },

        // 删除操作
        handleDelete(index, row) {
            const that = this;
            // 二次确认删除
            this.$confirm('只删除人脸信息，此操作不会删除用户的基本信息。确定要删除吗？', '提示', {
                type: 'warning'
            })
                .then(() => {
                    // this.$message.success('删除成功');
                    // this.tableData.splice(index, 1);
                    const id = this.tableData.splice(index, 1)[0].studentNumber;
                    console.log(id);
                    this.$axios
                        .post('/api/student/deleteOneFace/' + id)
                        .then((res) => {
                            //console.log(res);
                            if (res.data.error_code == 223103 || res.data.error_code == 223106) {
                                that.$message.error('人脸信息不存在');
                            }
                            if (res.data.error_code == 0 && res.data.state == 1) {
                                that.$message.success('人脸信息删除成功');
                            }
                            if (res.data.error_code == 222001) {
                                that.$message.error('人脸信息已为空，不用删除');
                            }
                            if (res.data == '') {
                                that.$message.error('删除失败');
                            }
                        })
                        .catch((err) => {
                            //console.error();
                            that.$message.error(`删除失败`);
                        });
                })
                .catch(() => {
                    this.$message({
                        type: 'info',
                        message: '已取消删除'
                    });
                });
        },
        // 多选操作
        handleSelectionChange(val) {
            this.multipleSelection = val;
        },
        delAllSelection() {
            const that = this;
            const length = this.multipleSelection.length;
            let str = '';
            if (length == 0) {
                this.$message.error(`请选择删除的对象`);
            } else {
                this.delList = this.delList.concat(this.multipleSelection);
                console.log(this.delList);

                for (let i = 0; i < length; i++) {
                    str += this.multipleSelection[i].studentNumber + ',';
                }
                this.$confirm('此操作将批量删除日志信息, 是否继续?', '提示', {
                    confirmButtonText: '确定',
                    cancelButtonText: '取消',
                    type: 'warning'
                })  
                    .then(() => {
                        console.log(str);
                        this.$axios.post('/api/student/deleteFaceMore', { studentNumber: str }).then((res) => {
                            console.log(res); // 服务器返回内容
                            if (res.data.error_code == 223103 || res.data.error_code == 223106) {
                                that.$message.error('人脸信息不存在');
                            }
                            if (res.data.error_code == 0 && res.data.state == 1) {
                                that.$message.error(`成功删除了${str}的人脸信息`);
                            } else {
                                that.$message.error('删除失败');
                            }
                            if (res.data.error_code == 222001) {
                                that.$message.error('人脸信息已为空，不用删除');
                            }
                            if (res.data == '') {
                                that.$message.error('删除失败');
                            }
                        });
                    })
                    .catch(() => {
                        this.$message({
                            type: 'info',
                            message: '已取消删除'
                        });
                    });

                // this.delList = this.delList.concat(this.multipleSelection);
                // console.log(this.delList);
                // for (let i = 0; i < length; i++) {
                //     str += this.multipleSelection[i].studentName + ' ';
                // }
                // for (let i = 0; i < length; i++) {
                //     str += this.multipleSelection[i].studentName + ' ';
                // }
                // this.$message.error(`删除了${str}`);
                // this.multipleSelection = [];
            }
        },

        handleAdd() {
            //this.addVisible = true;
            this.$router.push('/UploadFace');
        },

        handleUpload() {
            this.$router.push('/UpdateFace');
        },

        //详情信息
        handleMore(index, row) {
            this.idx = index;
            this.form = row;
            this.moreVisible = true;
        },
        // 编辑操作
        handleEdit(index, row) {
            this.idx = index;
            this.form = row;
            this.editVisible = true;
        },
        // 保存编辑
        saveEdit() {
            const that = this;
            this.editVisible = false;
            this.$set(this.tableData, this.idx, this.form);
            console.log(this.tableData[this.idx]);

            this.$axios
                .post('/api/student/updateOne', this.tableData[this.idx])
                .then((res) => {
                    console.log(res);
                    that.$message.success(`修改第 ${this.idx + 1} 行成功`);
                    // if (res && res.status === 200) {
                    //     this.loadLogInfo();
                    // }
                })
                .catch((err) => {
                    console.error();
                    that.$message.error(`修改失败`);

                    // message:“请添加记录”,
                    // type:‘warning’
                    // })
                    // type 取值 ‘success’ /warning/info/error/;
                });
            // .catch((err) => {
            //     console.log(err);
            // });
        },
        // 保存编辑
        saveAdd() {
            const that = this;
            this.addisible = false;
            // this.$set(this.tableData, this.idx, this.form);
            this.formAdd.studentAvatar = this.defaultAvatar;
            if (this.formAdd.studentName && this.formAdd.studentPassword && this.formAdd.studentNumber != null) {
               // console.log(this.formAdd);
                this.$axios
                    .post('/api/student/add', this.formAdd)
                    .then((res) => {
                        console.log(res);
                        if (res.status === 200) {
                            that.$message.success(`添加成功！`);
                            this.formAdd = {};
                            this.addVisible = false;
                        }

                        // if (res && res.status === 200) {
                        //     this.loadLogInfo();
                        // }
                    })
                    .catch((err) => {
                        console.error();
                        that.$message.error(`添加失败，账号已存在，请重新添加!`);
                    });
            } else {
                that.$message.error(`必填项未填`);
            }
        },

        // 分页导航
        handlePageChange(val) {
            console.log(val);
            this.$set(this.query, 'currentPage', val);
            this.getData();
        }
    }
};
</script>

<style scoped>
.handle-box {
    margin-bottom: 20px;
}

.handle-select {
    width: 120px;
}

.handle-input {
    width: 200px;
    display: inline-block;
}
/* .close {
    margin: 0 0 0 -30px;
} */

.table {
    width: 100%;
    font-size: 14px;
}
.red {
    color: #ff0000;
}
.blue {
    color: #2f00ff;
}
.mr10 {
    margin-right: 10px;
}
.table-td-thumb {
    display: block;
    margin: auto;
    width: 40px;
    height: 40px;
    cursor: pointer;
}

.table-td-thumb.el-icon-circle-close {
    color: white;
}
.handle-add {
    color: rgb(6, 49, 240);
}
</style>
