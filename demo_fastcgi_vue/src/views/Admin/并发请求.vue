<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item>
                    <i class="el-icon-lx-cascades"></i> 全部学生信息
                </el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <div class="handle-box">
                <el-button
                    type="primary"
                    icon="el-icon-delete"
                    class="handle-del mr10"
                    @click="delAllSelection"
                >批量删除</el-button>
                <el-select v-model="query.address" placeholder="地址" class="handle-select mr10">
                    <el-option key="1" label="广东省" value="广东省"></el-option>
                    <el-option key="2" label="湖南省" value="湖南省"></el-option>
                </el-select>
                <el-input v-model="query.name" placeholder="用户名" class="handle-input mr10"></el-input>
                <el-button type="primary" icon="el-icon-search" @click="handleSearch">搜索</el-button>
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
                <el-table-column prop="studentClass" label="班号" width="55" align="center"></el-table-column>
                <el-table-column prop="profession" label="专业" align="center"></el-table-column>
                <!-- <el-table-column prop="cardID" label="身份证号"></el-table-column> -->

                <el-table-column label="状态" align="center">
                    <template slot-scope="scope">
                        <el-tag
                            :type="scope.row.state==='成功'?'success':(scope.row.state==='失败'?'danger':'')"
                        >{{scope.row.state}}</el-tag>
                    </template>
                </el-table-column>

                <el-table-column prop="joinTime" label="注册时间" align="center"></el-table-column>

                <el-table-column label="头像(查看大图)" align="center">
                    <!-- scope.row  当前行的数据对象 -->
                    <template slot-scope="scope">
                        <el-image
                            class="table-td-thumb"
                            :src="scope.row.studentAvatar"
                            :preview-src-list="[scope.row.studentAvatar]"
                        ></el-image>
                    </template>
                </el-table-column>
                <el-table-column label="操作" width="180" align="center">
                    <template slot-scope="scope">
                        <el-button
                            type="text"
                            icon="el-icon-more"
                            class="blue"
                            @click="handleEdit(scope.$index, scope.row)"
                        >详情</el-button>
                        <el-button
                            type="text"
                            icon="el-icon-edit"
                            @click="handleEdit(scope.$index, scope.row)"
                        >编辑</el-button>
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

        <!-- 编辑弹出框 -->
        <el-dialog title="编辑" :visible.sync="editVisible" width="30%">
            <el-form ref="form" :model="form" label-width="70px">
                <el-form-item label="用户名">
                    <el-input v-model="form.name"></el-input>
                </el-form-item>
                <el-form-item label="地址">
                    <el-input v-model="form.address"></el-input>
                </el-form-item>
            </el-form>
            <span slot="footer" class="dialog-footer">
                <el-button @click="editVisible = false">取 消</el-button>
                <el-button type="primary" @click="saveEdit">确 定</el-button>
            </span>
        </el-dialog>
    </div>
</template>

<script>
import { fetchData } from '../../../api/index';
export default {
    name: 'basetable',
    data() {
        return {
            query: {
                address: '',
                name: '',
                currentPage: 1,
                pageSize: 5,
                pageTotal: 0
            },
            tableData: [],
            multipleSelection: [],
            delList: [],
            editVisible: false,
            form: {},
            idx: -1,
            id: -1
        };
    },
    created() {
        this.getData(); //渲染
    },
    methods: {
        // 获取后台数据
        getData() {
            const that = this;
            //axios的并发请求,//使用spread方法处理响应数组结果
            //this.$axios.defaults.baseURL='http://127.0.0.1:8888/';
            //var r1 = this.$axios.get('/api/student/findAllStudent');
            // var r2 = this.$axios.get('/api/student/index/', { params: { id: 123}});
            var r2 = this.$axios.get('/api/student/findStudent/' + 123);
            var r1 = this.$axios.get('/api/student/page?currentPage=' + this.query.currentPage);
            this.$axios
                .all([r1, r2])
                .then(
                    this.$axios.spread((res1, res2) => {
                        this.tableData = res1.data.data.records;
                        this.query.currentPage = res1.data.data.current;
                        this.query.pageTotal = res1.data.data.total;
                        this.query.pageSize = res1.data.data.size;

                        this.res2 = res2.data;
                        console.log('所有请求完成');
                        console.log('请求1结果', res1.data.data);
                        console.log('请求2结果', res2);
                        this.pageTotal = res1.idx;
                        console.log('总数', this.pageTotal);
                    })
                )
                .catch((err) => {
                    console.log(err);
                });


            // this.$axios.get('/api/student/index/'+123).then((res) => {
            //         console.log(res);
            //         that.$alert('操作成功', '提示', {
            //             confirmButtonText: '确定',
            //             callback: (action) => {
            //                 // that.$router.push('/blogs');
            //             }
            //         });
            //     });


            // fetchData(this.query).then((res) => {
            //     console.log("1111111111111111111"+res);
            //     this.tableData = res.list;
            //     console.log("1111111111111111111"+this.tableData );
            //      this.pageTotal = res.pageTotal || 50;
            // });
        },
        // 触发搜索按钮
        handleSearch() {
            this.$set(this.query, 'pageIndex', 1);
            this.getData();
        },
        // 删除操作
        handleDelete(index, row) {
            // 二次确认删除
            this.$confirm('确定要删除吗？', '提示', {
                type: 'warning'
            })
                .then(() => {
                    this.$message.success('删除成功');
                    this.tableData.splice(index, 1);
                })
                .catch(() => {});
        },
        // 多选操作
        handleSelectionChange(val) {
            this.multipleSelection = val;
        },
        delAllSelection() {
            const length = this.multipleSelection.length;
            let str = '';
            this.delList = this.delList.concat(this.multipleSelection);
            for (let i = 0; i < length; i++) {
                str += this.multipleSelection[i].name + ' ';
            }
            this.$message.error(`删除了${str}`);
            this.multipleSelection = [];
        },
        // 编辑操作
        handleEdit(index, row) {
            this.idx = index;
            this.form = row;
            this.editVisible = true;
        },
        // 保存编辑
        saveEdit() {
            this.editVisible = false;
            this.$message.success(`修改第 ${this.idx + 1} 行成功`);
            this.$set(this.tableData, this.idx, this.form);
        },
        // 分页导航
        handlePageChange(val) {
             this.$set(this.query, 'currentPage', val);
             this.getData();
        }
    },

    // mounted: function () {
    //     var me = this;
    //     this.$axios.all([me.getAllTask(), me.getAllCity()]).then(
    //         me.$axios.spread(function (allTask, allCity) {
    //             console.log('所有请求完成');
    //             console.log('请求1结果', allTask);
    //             console.log('请求2结果', allCity);
    //         })
    //     );
    // }
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
    width: 300px;
    display: inline-block;
}
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
</style>
