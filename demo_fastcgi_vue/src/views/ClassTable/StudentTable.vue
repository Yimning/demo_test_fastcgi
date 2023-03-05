<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-cascades"></i> 全部学生选课 </el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <div class="handle-box">
                <el-button type="danger" icon="el-icon-delete" class="handle-del mr10" @click="delAllSelection">批量删除</el-button>

                <el-select v-model="selected" placeholder="查询条件" class="handle-select mr10">
                    <el-option key="查课程号" label="课程号" value="0"></el-option>
                    <el-option key="查课程名" label="课程名" value="1"></el-option>
                </el-select>

                <el-input
                    v-model="query.request"
                    v-if="selected === '0'"
                    placeholder="输入课程号"
                    class="handle-input mr10"
                    @keyup.enter.native="handleSearch"
                    id="messageInput"
                    v-on:input="inputFunc"
                    clearable
                ></el-input>
                <!-- @keyup.enter 但是若在组件框架中写需要加.native -->
                <el-input
                    v-model="query.request"
                    v-else
                    placeholder="输入课程名"
                    class="handle-input mr10"
                    @keyup.enter.native="handleSearch"
                    id="messageInput"
                    v-on:input="inputFunc"
                    clearable
                ></el-input>

                <el-button v-if="showOrNot" type="warning" icon="el-icon-close" @click="handleClear">清除</el-button>
                <el-button type="primary" icon="el-icon-search" @click="handleSearch">搜索</el-button>
                <el-button type="success" icon="el-icon-circle-plus" @click="handleAdd">添加课程</el-button>
                <download-excel
                    class="handleUpload"
                    :fields="json_fields"
                    :data="multipleSelection"
                    :before-generate="startDownload"
                    :before-finish="finishDownload"
                    type="xls"
                >
                    <el-button type="info" icon="el-icon-download">导出</el-button>
                </download-excel>
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
                <el-table-column prop="studentSex" label="性别" width="55" align="center"> </el-table-column>
                <el-table-column prop="studentClass" label="班号" width="55" align="center"></el-table-column>
                <el-table-column prop="profession" label="专业" align="center"></el-table-column>
                <el-table-column prop="courseID" label="课程号" align="center"></el-table-column>
                <el-table-column prop="courseName" label="课程名" align="center"></el-table-column>
                <el-table-column prop="teacherNumber" label="教师号" align="center"></el-table-column>
                <el-table-column prop="teacherName" label="授课教师" align="center"></el-table-column>
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
    </div>
</template>

<script>
import { fetchData, AvatarData } from '../../api/index';
import JsonExcel from 'vue-json-excel';
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
            multipleSelection: [],
            list: [{}],
            json_fields: {
                学号: 'studentNumber',
                姓名: 'studentName',
                性别: 'studentSex',
                班号: 'studentClass',
                专业: 'profession',
                课程号: 'courseID',
                课程名: 'courseName',
                教师号: 'teacherNumber',
                授课教师: 'teacherName'
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
    components: {
        'download-excel': JsonExcel
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
                .get('/api/scourse/findAllScourse')
                .then((res) => {
                    // console.log(res);
                    // this.tableData = res.data.data;
                    // // console.log('请求后台数据结果', res.data.data);
                    this.list = [];
                    let newArray = [];
                    for (const i in res.data) {
                        for (const key in res.data[i].course) {
                            //console.log("属性:"+key);
                            this.$set(this.list, key, res.data[i].course[key]); //对象新增属性(使用Vue.$set())
                            newArray[i] = this.list; //新建数组存放
                            // this.list.push(i + ':' + JSON.stringify(res.data[k].course[i]));
                        }
                        for (const key in res.data[i].student) {
                            //console.log("属性:"+key);
                            this.$set(this.list, key, res.data[i].student[key]); //对象新增属性(使用Vue.$set())
                            newArray[i] = this.list; //新建数组存放
                            // this.list.push(i + ':' + JSON.stringify(res.data[k].course[i]));
                        }
                        for (const key in res.data[i].teacher) {
                            //console.log("属性:"+key);
                            this.$set(this.list, key, res.data[i].teacher[key]); //对象新增属性(使用Vue.$set())
                            newArray[i] = this.list; //新建数组存放
                            // this.list.push(i + ':' + JSON.stringify(res.data[k].course[i]));
                        }
                        this.list = []; //循环完必须清空,否则可能会覆盖
                    }
                    this.tableData = newArray;
                    this.query.currentPage = 1;
                    this.query.pageTotal = res.data.length;
                    this.query.pageSize = res.data.length;
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
            this.handleSearch();
        },
        // 触发搜索按钮
        handleSearch() {
            // console.log(this.query.request);//打印输入搜索的值
            this.tableData = [];
            const that = this;
            const findByID = '/api/scourse/findScourseBycourseID/';
            const findByName = '/api/scourse/findScourseByName/';
            //console.log(this.selected);
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
                .get(val, { params: { id: this.query.request } })
                .then((res) => {
                    //console.log(res);
                    if (res.data[0] == null) {
                        this.$message.error(`无记录`);
                        that.query.currentPage = 0;
                        that.query.pageTotal = res.data.length;
                        that.query.pageSize = res.data.length;
                    } else {
                        this.list = [];
                        let newArray = [];
                        for (const i in res.data) {
                            for (const key in res.data[i].course) {
                                //console.log("属性:"+key);
                                this.$set(this.list, key, res.data[i].course[key]); //对象新增属性(使用Vue.$set())
                                newArray[i] = this.list; //新建数组存放
                                // this.list.push(i + ':' + JSON.stringify(res.data[k].course[i]));
                            }
                            for (const key in res.data[i].student) {
                                //console.log("属性:"+key);
                                this.$set(this.list, key, res.data[i].student[key]); //对象新增属性(使用Vue.$set())
                                newArray[i] = this.list; //新建数组存放
                                // this.list.push(i + ':' + JSON.stringify(res.data[k].course[i]));
                            }
                            for (const key in res.data[i].teacher) {
                                //console.log("属性:"+key);
                                this.$set(this.list, key, res.data[i].teacher[key]); //对象新增属性(使用Vue.$set())
                                newArray[i] = this.list; //新建数组存放
                                // this.list.push(i + ':' + JSON.stringify(res.data[k].course[i]));
                            }
                            this.list = []; //循环完必须清空,否则可能会覆盖
                        }
                        this.tableData = newArray;
                        this.query.currentPage = 1;
                        this.query.pageTotal = res.data.length;
                        this.query.pageSize = res.data.length;
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
            this.$confirm('确定要删除吗？', '提示', {
                type: 'warning'
            })
                .then(() => {
                    // this.$message.success('删除成功');
                    // this.tableData.splice(index, 1);
                    const id = this.tableData.splice(index, 1)[0].studentNumber;
                    console.log(id);
                    this.$axios
                        .post('/api/student/deleteOne/' + id)
                        .then((res) => {
                            console.log(res);
                            that.$message.success('删除成功');
                        })
                        .catch((err) => {
                            console.error();
                            that.$message.success(`删除失败`);
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
                        this.$axios.post('/api/student/deleteMore', { studentNumber: str }).then((res) => {
                            if (res && res.status === 200) {
                                console.log(res.data); // 服务器回包内容
                                that.$message.error(`删除了${str}`);
                            }
                        });
                    })
                    .catch(() => {
                        this.$message({
                            type: 'info',
                            message: '已取消删除'
                        });
                    });
            }
        },
        startDownload() {
            let self = this;
            if (self.multipleSelection.length == 0) {
                self.$message({
                    message: '警告，请勾选数据',
                    type: 'warning'
                });
            }
        },
        finishDownload() {
            let self = this;
            self.$message({
                message: '恭喜，数据导出成功',
                type: 'success'
            });
        },

        handleAdd() {
            this.$router.push('/addCourse');
        },

        handleUpload() {},

        // 分页导航
        handlePageChange(val) {
            //console.log(val);
            this.$set(this.query, 'currentPage', val);
            this.getData();
        }
    }
};
</script>

<style scoped>
.handleUpload {
    position: relative;
    margin-left: 720px;
    margin-top: -32px;
}
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
