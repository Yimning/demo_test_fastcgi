<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-cascades"></i> 签到情况 </el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <div class="handle-box" ref="QueryConditions" :rules="rules">
                <el-button type="danger" icon="el-icon-delete" class="handle-del mr10" @click="delAllSelection" disabled
                    >批量删除</el-button
                >
                <el-select v-model="QueryConditions" placeholder="课程号-课程名" class="mr10" v-on:input="courseFunc">
                    <el-option
                        el-option
                        :key="QueryConditions.courseID"
                        :label="QueryConditions.courseID + QueryConditions.course.courseName"
                        :value="QueryConditions.courseID"
                    ></el-option>
                </el-select>

                <el-select v-model="selected" placeholder="查询条件" v-on:input="selectedFunc" class="handle-select mr10">
                    <el-option key="查教师号" label="教师号" value="0" v-if="isTeacher"></el-option>
                    <el-option key="查学号" label="查学号" value="1" v-else></el-option>
                </el-select>

                <el-input
                    v-model="query.request"
                    v-if="selected === '0'"
                    placeholder="教师号"
                    class="handle-input mr10"
                    @keyup.enter.native="handleSearch"
                    id="messageInput"
                    v-on:input="inputFunc"
                    clearable
                    disabled
                ></el-input>
                <el-input
                    v-model="query.request"
                    v-if="selected === '1'"
                    placeholder="学号"
                    class="handle-input mr10"
                    @keyup.enter.native="handleSearch"
                    id="messageInput"
                    v-on:input="inputFunc"
                    clearable
                    disabled
                ></el-input>
                <div>
                    <el-button class="handle-line" type="primary" plain icon="el-icon-refresh" @click="handleFresh">条件重置</el-button>
                    <el-button type="success" icon="el-icon-circle-check" @click="handleFlag">应出勤</el-button>
                    <el-button type="warning" icon="el-icon-circle-close" @click="handleNotFlag">缺勤</el-button>
                    <el-button type="primary" icon="el-icon-notebook-1" @click="handleNow">课程出勤率</el-button>
                    <el-button type="info" icon="el-icon-data-analysis" @click="handleHistory">历史记录</el-button>
                    <el-button type="success" plain icon="el-icon-s-flag" @click="handleCheck">个人出勤率查询</el-button>
                </div>
                <div>
                    <download-excel
                        class="handleUpload"
                        :fields="json_fields"
                        :data="multipleSelection"
                        :before-generate="startDownload"
                        :before-finish="finishDownload"
                        type="xls"
                    >
                        <el-button type="info" icon="el-icon-download">导出</el-button>
                        <!-- <el-button type="info" icon="el-icon-download" @click="handleAllUpload">全部导出</el-button> -->
                    </download-excel>
                </div>
            </div>

            <el-table
                :data="tableData"
                border
                class="table"
                ref="multipleTable"
                header-cell-class-name="table-header"
                @selection-change="handleSelectionChange"
            >
                <el-table-column type="selection" width="40" align="center"></el-table-column>
                <el-table-column prop="recordID" label="记录号" width="55" align="center"></el-table-column>
                <el-table-column prop="studentNumber" label="学号" align="center"></el-table-column>
                <el-table-column prop="studentName" label="姓名" align="center"></el-table-column>
                <el-table-column prop="studentSex" label="性别" width="55" align="center"> </el-table-column>
                <el-table-column prop="studentClass" label="班号" width="55" align="center"></el-table-column>
                <el-table-column prop="profession" label="专业" align="center"></el-table-column>
                <el-table-column prop="courseID" label="课程号" width="55" align="center"></el-table-column>
                <el-table-column prop="courseName" label="课程名" align="center"></el-table-column>
                <!-- <el-table-column prop="teacherNumber" label="教师号" align="center"></el-table-column> -->
                <el-table-column prop="teacherName" label="授课教师" align="center"></el-table-column>
                <el-table-column prop="recordTime" label="签到时间" align="center"></el-table-column>
                <el-table-column prop="weekDay" label="星期" align="center"></el-table-column>
                <el-table-column prop="flag" label="是否已签" align="center"></el-table-column>
                <el-table-column label="操作" width="180" align="center">
                    <template slot-scope="scope">
                        <el-button type="text" icon="el-icon-more" class="blue" @click="handleMore(scope.$index, scope.row)"
                            >统计</el-button
                        >
                        <el-button type="text" icon="el-icon-edit" @click="handleEdit(scope.$index, scope.row)" v-if="isTeacher"
                            >补签</el-button
                        >
                        <el-button
                            type="text"
                            icon="el-icon-delete"
                            class="red"
                            @click="handleEdit1(scope.$index, scope.row)"
                            v-if="isTeacher"
                            >缺勤</el-button
                        >
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
        <!-- 统计 -->
        <el-dialog title="" :visible.sync="moreVisible" width="30%">
            <el-form ref="count" :model="{ count }" label-width="70px">
                <el-form-item label="班号">
                    <el-input v-model="count.studentClass" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="学号">
                    <el-input v-model="count.studentNumber" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="姓名">
                    <el-input v-model="count.studentName" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="性别">
                    <el-input v-model="count.studentSex" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="专业">
                    <el-input v-model="count.profession" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="课程号">
                    <el-input v-model="count.courseID" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="课程名">
                    <el-input v-model="count.courseName" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="课程时间">
                    <el-input v-model="count.courseTime" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="出勤次数">
                    <el-input v-model="count.isFlag" readonly="readonly"></el-input>
                </el-form-item>
                <el-form-item label="缺勤次数">
                    <el-input v-model="count.notFlag" readonly="readonly"></el-input>
                </el-form-item>
            </el-form>
            <span slot="footer" class="dialog-footer">
                <el-button @click="moreVisible = false">取 消</el-button>
                <el-button type="primary" @click="handleDetails">详情信息</el-button>
            </span>
        </el-dialog>
    </div>
</template>

<script>
import { fetchData, AvatarData } from '../../api/index';
import JsonExcel from 'vue-json-excel';
const weekArr = ['星期日', '星期一', '星期二', '星期三', '星期四', '星期五', '星期六'];
export default {
    name: 'basetable',
    inject: ['reload'],
    data() {
        return {
            query: {
                address: '',
                name: '',
                currentPage: 1,
                pageSize: 5,
                pageTotal: 0,
                request: this.$store.getters.getUser.userID
            },
            form: {
                options: []
            },
            timeValue: '',
            input: '',
            newArray: [],
            QueryConditions: {
                IsDay: '',
                courseID: '',
                courseName: '',
                course: {}
            },
            queryInfo: {
                courseID: '',
                courseName: ''
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
                授课教师: 'teacherName',
                签到时间: 'recordTime',
                星期: 'weekDay',
                是否已签: 'flag'
            },
            weeks: {
                0: '星期日',
                1: '星期一',
                2: '星期二',
                3: '星期三',
                4: '星期四',
                5: '星期五',
                6: '星期六'
            },
            rules: {
                recordTime: [{ required: true, message: '请输入密保答案', trigger: 'blur' }]
            },
            requestAddr: '',
            url: '',
            selected: '0', //注意数据格式的转换，否则会导致不正常
            tableData: [],
            paramsData: [],
            count: {
                isFlag: '',
                notFlag: ''
            },
            recentAttendanceStu: [],
            recentAttendanceList: [],
            recentAttendanceInfo: {
                allFlag: '',
                notFlag: ''
            },
            params: {},
            multipleSelection: [],
            delList: [],
            teacherAdmin: false,
            isTeacher: false,
            moreVisible: false,
            showOrNot: false,
            form: {},
            defaultAvatar: {},
            idx: -1,
            row: '',
            id: -1
        };
    },
    components: {
        'download-excel': JsonExcel
    },
    created() {
        if (this.$store.getters.getUser.roseName == '教师') {
            this.teacherAdmin = true;
        }
        this.getData(); //渲染
        this.getAllCourse();
        AvatarData(this.defaultAvatar).then((res) => {
            this.defaultAvatar = res.avatar[0].base64;
        });
        const url = '/api/attendance/findAttendanceInfo';
        //学生
        if (this.$store.getters.getUser.roseID == '0') {
            this.selected = '1';
            this.params = {
                params: {
                    courseID: null,
                    studentNumber: this.$store.getters.getUser.userID,
                    studentName: null,
                    teacherNumber: null,
                    teacherName: null,
                    flag: null,
                    time: null
                }
            };
            this.StuAttendenceRecords(url, this.params);
        }
        //教师
        if (this.$store.getters.getUser.roseID == '1') {
            this.isTeacher = true; //只有教师显示
            this.params = {
                params: {
                    courseID: null,
                    studentNumber: null,
                    studentName: null,
                    teacherNumber: this.$store.getters.getUser.userID,
                    teacherName: null,
                    flag: null,
                    time: null
                }
            };
            this.TeachAttendenceRecords(url, this.params);
        }
    },

    methods: {
        // 获取后台数据
        getData() {
            const that = this;
            if (this.$store.getters.getUser.roseID == '1') {
            }
        },

        // 获取全部课程数据
        getAllCourse() {},
        StuAttendenceRecords(url, params) {
            const that = this;
            const url1 = '/api/scourse/findScourseByteacherNumbercIDcD';
            const url2 = '/api/attendance/findAttendanceInfo';
            //axios的get请求
            this.$axios
                .get(url, params)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', res);
                    if (res.data.length != 0) {
                        this.json = res.data[0];
                        console.log('this.json数据结果', this.json);
                        this.newArray = this.dataTraversal(this.form);
                        this.QueryConditions = res.data[0];
                        const params1 = {
                            params: {
                                tID: this.json.teacher.teacherNumber,
                                cID: this.json.courseID,
                                cD: null
                            }
                        };
                        const params2 = {
                            params: {
                                courseID: this.json.courseID,
                                studentNumber: null,
                                studentName: null,
                                teacherNumber: this.json.teacher.teacherNumber,
                                teacherName: null,
                                flag: 0,
                                time: this.json.recordTime
                            }
                        };
                        this.recentAttendanceFlag(url1, params1, url2, params2);
                    }
                })
                .catch((err) => {
                    console.log(err);
                });
        },
        TeachAttendenceRecords(url, params) {
            const that = this;
            const url1 = '/api/scourse/findScourseByteacherNumbercIDcD';
            const url2 = '/api/attendance/findAttendanceInfo';
            //axios的get请求
            this.$axios
                .get(url, params)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', res);
                    if (res.data.length != 0) {
                        this.json = res.data[0];
                        //console.log('this.json数据结果', this.json);
                        this.newArray = this.dataTraversal(this.form);
                        this.QueryConditions = res.data[0];
                        const params1 = {
                            params: {
                                tID: this.json.teacher.teacherNumber,
                                cID: this.json.courseID,
                                cD: null
                            }
                        };
                        const params2 = {
                            params: {
                                courseID: this.json.courseID,
                                studentNumber: null,
                                studentName: null,
                                teacherNumber: this.$store.getters.getUser.userID,
                                teacherName: null,
                                flag: 0,
                                time: this.json.recordTime
                            }
                        };
                        this.recentAttendanceFlag(url1, params1, url2, params2);
                    }
                })
                .catch((err) => {
                    console.log(err);
                });
        },
        recentAttendanceFlag(url1, params1, url2, params2) {
            const that = this;
            var r0 = this.$axios.get(url1, params1);
            var r1 = this.$axios.get(url2, params2);
            //并发请求
            this.$axios
                .all([r0, r1])
                .then(
                    that.$axios.spread((res1, res2) => {
                        console.log(res1, res2);
                        this.recentAttendanceStu = this.dataTraversal(res1.data);
                        this.recentAttendanceList = this.dataTraversal(res2.data);
                        this.tableData = this.recentAttendanceList;
                        this.recentAttendanceInfo.allFlag = res1.data.length;
                        this.recentAttendanceInfo.notFlag = res2.data.length;
                    })
                )
                .catch((err) => {
                    console.log(err);
                });
        },
        dataTraversal(form) {
            this.list = [];
            this.newArray = [];
            for (const i in form) {
                //console.log('属性:' + i);
                this.$set(this.list, 'recordID', form[i].recordID);
                this.$set(this.list, 'recordTime', form[i].recordTime);
                this.$set(this.list, 'flag', form[i].flag);
                this.$set(this.list, 'weekDay', this.dataDateChange(form[i].recordTime));

                for (const key in form[i].course) {
                    this.$set(this.list, key, form[i].course[key]); //对象新增属性(使用Vue.$set())
                    this.newArray[i] = this.list; //新建数组存放
                }
                for (const key in form[i].student) {
                    //console.log("属性:"+key);
                    this.$set(this.list, key, form[i].student[key]); //对象新增属性(使用Vue.$set())
                    this.newArray[i] = this.list; //新建数组存放
                }
                for (const key in form[i].teacher) {
                    //console.log("属性:"+key);
                    this.$set(this.list, key, form[i].teacher[key]); //对象新增属性(使用Vue.$set())
                    this.newArray[i] = this.list; //新建数组存放
                }
                this.list = []; //循环完必须清空,否则可能会覆盖
            }
            return this.newArray;
            this.query.currentPage = 1;
            this.query.pageTotal = form.length;
            this.query.pageSize = form.length;
        },
        // 时间格式化
        dataFormat(value) {
            if (value != null || value == '') {
                var year = value.substr(0, 4);
                var month = value.substr(5, 2);
                var day = value.substr(8, 2);
                var hour = value.substr(11, 2);
                var min = value.substr(14, 2);
                var second = value.substr(17, 2);
                return year + '-' + month + '-' + day + ' ' + hour + ':' + min + ':' + second;
            } else return null;
        },
        //根据当前的日期显示当前是星期几
        dataDateChange(dateStr) {
            if (dateStr != null || dateStr == '') {
                let date = new Date(dateStr);
                let weekIndex = date.getDay();
                //this.week = this.weeks[weekIndex];
                return this.weeks[weekIndex];
            } else return null;
        },
        GMTToStr: function (time) {
            let date = new Date(time);
            let Str =
                date.getFullYear() +
                '-' +
                (date.getMonth() + 1) +
                '-' +
                date.getDate() +
                ' ' +
                date.getHours() +
                ':' +
                date.getMinutes() +
                ':' +
                date.getSeconds();
            return Str;
        },
        StrToGMT(time) {
            let GMT = new Date(time);
            return GMT;
        },
        //清除搜索框
        handleClear() {
            this.query.request = '';
            this.showOrNot = false;
            this.getData();
        },
        courseFunc(e) {
            const url = '/api/attendance/findAttendanceInfo';
            //console.log(e)   //课程号
            this.getAttendanceBycourseID(url, e);
        },
        // 获取课程BycourseID
        getAttendanceBycourseID(url, id) {
            const that = this;
            //axios的get请求
            this.params = {
                params: {
                    courseID: id,
                    studentNumber: null,
                    studentName: null,
                    teacherNumber: this.$store.getters.getUser.userID,
                    teacherName: null,
                    flag: null,
                    time: null
                }
            };
            this.$axios
                .get(url, this.params)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', this.form);
                    this.dataTraversal(this.form);
                })
                .catch((err) => {
                    //console.log(err);
                    this.$message({
                        type: 'info',
                        message: '请正确选择'
                    });
                });
        },
        // 获取课程BystudentID
        getAttendanceBystudentID(url, params) {
            const that = this;
            //axios的get请求
            this.$axios
                .get(url, params)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', this.form);
                    this.dataTraversal(this.form);
                })
                .catch((err) => {
                    console.log(err);
                });
        },
        // 获取课程BystudentName
        getAttendanceBystudentName(url, params) {
            const that = this;
            //axios的get请求
            this.$axios
                .get(url, params)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', this.form);
                    this.dataTraversal(this.form);
                })
                .catch((err) => {
                    console.log(err);
                });
        },
        // 获取课程ByteacherID
        getAttendanceByteacherID(url, params) {
            const that = this;
            //axios的get请求
            this.$axios
                .get(url, params)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', this.form);
                    this.dataTraversal(this.form);
                })
                .catch((err) => {
                    console.log(err);
                });
        },
        // 获取课程ByteacherName
        getAttendanceByteacherName(url, params) {
            const that = this;
            //axios的get请求
            this.$axios
                .get(url, params)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', this.form);
                    this.dataTraversal(this.form);
                })
                .catch((err) => {
                    console.log(err);
                });
        },
        // 获取课程ByteacherName
        getAttendanceByInfo(url, json) {
            const that = this;
            //axios的get请求
            this.$axios
                .get(url, json)
                .then((res) => {
                    this.form = res.data;
                    //console.log('请求后台数据结果', this.form);
                    this.dataTraversal(this.form);
                })
                .catch((err) => {
                    console.log(err);
                });
        },

        //监听事件-输入框
        inputFunc(e) {
            this.handleSearch(e);
        },
        handleSearchByInfo() {
            if (!this.QueryConditions.courseID && !this.QueryConditions.recordTime) return this.$message.error(`请选择时间和课程号查询`);
            if (!this.QueryConditions.courseID) return this.$message.error(`选择课程号-课程名`);
            if (!this.QueryConditions.recordTime) return this.$message.error(`选择时间查询`);

            if (this.QueryConditions.courseID && this.QueryConditions.recordTime) {
                const url = '/api/attendance/findAttendanceInfo';
                this.params = {
                    params: {
                        courseID: this.QueryConditions.courseID,
                        studentNumber: null,
                        studentName: null,
                        teacherNumber: null,
                        teacherName: null,
                        flag: null,
                        time: this.QueryConditions.recordTime
                    }
                };
                this.getAttendanceByInfo(url, this.params);
            }
        },
        selectedFunc() {
            this.query.request = '';
        },

        inputFuncDay(value) {
            if (!value) return;
            let date = new Date(value);
            let weekIndex = date.getDay();
            this.QueryConditions.IsDay = weekArr[weekIndex];
        },
        // 触发搜索按钮
        handleSearch(value) {},

        //详情信息
        handleMore(index, row) {
            this.idx = index;
            this.row = row;
            const that = this;
            const url = '/api/attendance/countAttendanceNotflag';
            const params = { params: { flag: 0, cID: row.courseID, sID: row.studentNumber } };
            const url1 = '/api/attendance/countAttendanceIsflag';
            const params1 = { params: { flag: 1, cID: row.courseID, sID: row.studentNumber } };
            var r0 = this.$axios.get(url, params);
            var r1 = this.$axios.get(url1, params1);
            //并发请求
            this.$axios
                .all([r0, r1])
                .then(
                    that.$axios.spread((res1, res2) => {
                        this.count.notFlag = res1.data.length;
                        this.count.isFlag = res2.data.length;
                    })
                )
                .catch((err) => {
                    console.log(err);
                });
            this.count = row;
            this.moreVisible = true;
        },
        // 补签操作
        handleEdit(index, row) {
            this.idx = index;
            const that = this;
            //console.log(row);
            const url = '/api/attendance/updateAttendanceInfo';
            var obj = {};
            for (var i in row) {
                obj[i] = row[i];
            }
            // console.log(Object.keys(row)[0]);
            // console.log(Object.values(row)[0]);
            const params = obj;
            //axios的get请求
            this.$axios
                .post(url, params)
                .then((res) => {
                    //console.log('请求后台数据结果', res);
                    if (res.data === 0) return this.$message.error(`补签失败,请重试！`);
                    if (res.data === 1) {
                        this.$message.success(`补签成功`);
                        return this.reload(); //刷新 ----推荐
                    }
                    if (res.data === 2) return this.$message.success(`已签,无需重复操作`);
                })
                .catch((err) => {
                    this.$message.error(` Request failed with status code 400`);
                });
        },
        // 记未签操作
        handleEdit1(index, row) {
            this.idx = index;
            const that = this;
            // console.log(row);
            const url = '/api/attendance/updateAttendanceInfo1';
            var obj = {};
            for (var i in row) {
                obj[i] = row[i];
            }
            const params = obj;
            this.$confirm('确定要操作吗？', '提示', {
                type: 'warning'
            })
                .then(() => {
                    that.$axios
                        .post(url, params)
                        .then((res) => {
                            //console.log('请求后台数据结果', res);
                            if (res.data === 0) return that.$message.error(`记缺勤失败,请重试！`);
                            if (res.data === 1) {
                                that.$message.success(`记缺勤成功`);
                                return that.reload(); //刷新 ----推荐
                            }
                            if (res.data === 2) return this.$message.error(`已缺勤,无需重复操作`);
                        })
                        .catch((err) => {
                            this.$message.error(` Request failed with status code 400`);
                        });
                })
                .catch(() => {
                    this.$message({
                        type: 'info',
                        message: '已取消'
                    });
                });

            //axios的get请求
        },
        arrayToObject(data) {},

        // 删除操作
        handleDelete(index, row) {},
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
                    str += this.multipleSelection[i].recordID + ',';
                }
                this.$confirm('此操作将批量删除日志信息, 是否继续?', '提示', {
                    confirmButtonText: '确定',
                    cancelButtonText: '取消',
                    type: 'warning'
                })
                    .then(() => {
                        console.log(str);
                        this.$axios.post('/api/attendance/deleteMore', { recordID: str }).then((res) => {
                            if (res && res.status === 200) {
                                // console.log(res.data); // 服务器回包内容
                                that.$message.error(`删除了${str}`);
                                return that.reload(); //刷新 ----推荐
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

        handleAllUpload() {},
        handleDetails() {},
        handleFresh() {
            return this.reload(); //刷新 ----推荐
        },
        handleFlag() {
            this.isTeacher = false;
            this.tableData = this.recentAttendanceStu;
        },

        handleNotFlag() {
            this.tableData = this.recentAttendanceList;
        },
        requestHandle(url, params) {},
        // 分页导航
        handlePageChange(val) {
            //console.log(val);
            this.$set(this.query, 'currentPage', val);
            this.getData();
        },
        handleNow() {
            let self = this;
            let number = (this.recentAttendanceInfo.allFlag - this.recentAttendanceInfo.notFlag) / this.recentAttendanceInfo.allFlag;
            let str = Number(number * 100).toFixed(2);
            str += '%';
            // this.testCoverages = str;
            // var str = Number(point * 100).toFixed(1);
            // str += '%';
            self.$message({
                message: '本次课程出勤率为:' + str,
                type: 'success'
            });
        },
        handleCheck() {
            if (this.$store.getters.getUser.roseID == '0') {
                this.$router.push('/stuAttendenceRecords');
            } else {
                this.$router.push('/attendenceQuery');
            }
        },
        handleHistory() {
            if (this.$store.getters.getUser.roseID == '0') {
                this.$router.push('/stuAttendenceRecords');
            } else {
                this.$router.push('/attendenceRecords');
            }
        }
    }
};
</script>

<style scoped>
.container {
    position: relative;
}
.handleUpload {
    position: relative;
    margin-left: 850px;
    margin-top: -32px;
}
.handle-box {
    margin-bottom: 20px;
    display: block;
}
.handle-line {
    position: relative;
    margin-left: 2px;
    margin-bottom: 0px;
    margin-right: 0px;
    margin-top: 8px;
}
.handle-weekday {
    position: relative;
    margin-left: 570px;
    margin-top: -32px;
}

.handle-select {
    width: 120px;
}

.handle-input {
    width: 120px;
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
